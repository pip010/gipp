
#pragma once

#include <scoped_pointer.hpp>

#include <tuple>
//#include <utility>
#include <type_traits>
#include <cassert>

#include <itkProcessObject.h>
//#include <itkDataObject.h>
#include <itkImage.h>

#include <itkCommand.h>

namespace gipp
{
	namespace details
	{
		/*
		class MyCommand : public itk::Command
		{
		  public:
		    itkNewMacro( MyCommand );

		  public:

		    void Execute(itk::Object *caller, const itk::EventObject & event)
		    {
		      Execute( (const itk::Object *)caller, event);
		    }

		    void Execute(const itk::Object * object, const itk::EventObject & event)
		    {
		      std::cout << "Command called." << std::endl;
		    }

		};
		*/

		//entirelly artifical since we have VS2013 bug here
		template<std::size_t I, typename... Tp>
		struct comparator
		{
			static const bool value = (I < sizeof...(Tp));
		};

		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< !comparator<I, Tp...>::value, void>::type
			for_each(std::tuple<Tp...>&, FuncT&)
		{
		}

		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< comparator<I, Tp...>::value, void>::type
			for_each(std::tuple<Tp...>& t, FuncT& f)
		{
			f(I,std::get<I>(t).GetPointer());
			for_each<I + 1, FuncT, Tp...>(t, f);
		}


		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< !comparator<I, Tp...>::value, void>::type
			for_each_update(std::tuple<Tp...>&, FuncT&)
		{
		}

		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< comparator<I, Tp...>::value, void>::type
			for_each_update(std::tuple<Tp...>& t, FuncT& f)
		{
			f.set(I,std::get<I>(t).GetPointer());
			std::get<I>(t).GetPointer()->Update();
			f.get(I,std::get<I>(t).GetPointer());
			for_each_update<I + 1, FuncT, Tp...>(t, f);
		}

		template<std::size_t I, typename... Tp>
		struct hook_helper
		{
			static const bool last = (I == sizeof...(Tp));
			static const bool first = (I == 0);
		};

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if< hook_helper<I, Tp...>::last, void>::type
			hook(std::tuple<Tp...>&)
		{}

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if< !hook_helper<I, Tp...>::first && !hook_helper<I, Tp...>::last , void>::type
			hook(std::tuple<Tp...>& t)
		{
			auto& filter_this = std::get<I>(t);

			auto& filter_prev = std::get<I-1>(t);

			filter_this.GetPointer()->SetInput(
				filter_prev.GetPointer()->GetOutput()
				);

			hook<I + 1, Tp...>(t);
		}

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if< hook_helper<I, Tp...>::first, void>::type
			hook(std::tuple<Tp...>& t)
		{
			hook<I + 1, Tp...>(t);
		}

		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< !comparator<I, Tp...>::value, void>::type
			for_each_update2(std::tuple<Tp...>&, FuncT&)
		{
		}

		template<std::size_t I = 0, typename FuncT, typename... Tp>
		inline typename std::enable_if< comparator<I, Tp...>::value, void>::type
			for_each_update2(std::tuple<Tp...>& t, FuncT& f)
		{
			// f.set(I,std::get<I>(t).GetPointer());
			// std::get<I>(t).GetPointer()->Update();
			// f.get(I,std::get<I>(t).GetPointer());

			f.set(std::get<I>(t));
			std::get<I>(t).GetPointer()->Update();
			f.get(std::get<I>(t));

			for_each_update<I + 1, FuncT, Tp...>(t, f);
		}



	}//namespace details

	template<typename Timage, typename... Tfilters>
	struct gpipe
	{
		gpipe()
		{
			details::hook(pipe);
		}

		// ASSERT supported by ITK image types (a subset maybe)
		//static_assert(std::is_integral<Timage>::value  || std::is_floating_point<Timage>::value, "Image voxel type must be an integral type.");

		const unsigned int depth = sizeof...(Tfilters);

		typedef std::tuple<Tfilters ...> TupleType;
		TupleType pipe;

		typedef Timage ImageType;

		template< typename Tfunc>
		void Update(Tfunc& f)
		{
			details::for_each_update(pipe,f);
		}

		template< typename Tfunc>
		void Apply(Tfunc& f)
		{
			details::for_each(pipe,f);
		}

		itk::ProcessObject* First() const
		{
			return std::get<0>(pipe).GetPointer();
		}

		itk::ProcessObject* Last() const
		{
			return std::get<sizeof...(Tfilters)-1>(pipe).GetPointer();
		}
	};


////////////////////////////////////////////////////////////////////////////////


template<typename Timage, typename... Tfilters>
struct gpipe2
{
	const unsigned int depth = sizeof...(Tfilters);

	typedef std::tuple<Tfilters ...> TupleType;
	TupleType pipe;

	using ImageType = Timage;

	gpipe2()
	{
		details::hook(pipe);
	}

	template< typename Tfunc>
	void Update(Tfunc& f)
	{
		details::for_each_update2(pipe,f);
	}
};

template< typename Tfilter, int I = 0>
struct node
{
	static_assert(std::is_base_of<itk::ProcessObject, Tfilter>::value, "must be inhereting from itk::ProcessObject");

	const int id = I;

	node()
	{
		sp = Tfilter::New();
	}

	void Update()
	{
		sp->Update();
	}

	void PrintSelf()
	{
		sp->Print(std::cout,itk::Indent(1));
	}

	Tfilter* Get() const
	{
		return sp.GetPointer();
	}

private:
	itk::SmartPointer<Tfilter> sp;
};

}
