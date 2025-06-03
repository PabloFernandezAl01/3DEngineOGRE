#pragma once
#include <memory>
#include <cassert>

/*
 * This is an attempt to have a single Singleton class that can be used
 * via inheritance to make some other class Singleton. It is just to avoid
 * copying the Singleton declarations each time.
 *
 * >>> Requirements:
 *
 * The class that inherits this class must implement a constructor
 * with no arguments, this is because of the call 'init()' in method
 * 'instance()'. In the case that defining such a constructor is against
 * your design, just define one that throws and exception.
 */

namespace Core {

	template<typename T>
	class ESingleton {

	protected:
		ESingleton() {}

	public:

		// cannot copy objects of this type
		ESingleton<T>& operator=(const ESingleton<T>& o) = delete;
		ESingleton(const ESingleton<T>& o) = delete;

		virtual ~ESingleton() {}

		virtual bool Valid() {
			return true;
		}

		// some singletons need to be initialised with some parameters, we
		// can call this method at the beginning of the program.
		template<typename ...Targs>
		inline static T* Init(Targs &&...args) {
			assert(instance_.get() == nullptr);
			instance_.reset(new T(std::forward<Targs>(args)...));
			return instance_.get();
		}

		// in some cases, when singletons depend on each other, you have
		// to close them in a specific order, This is why we have this close
		// method
		inline static void Close() {
			instance_.reset();
		}

		// get the singleton instance as a pointer
		//
		inline static T* Instance() {
			// you can replace the "if" by assert(instance_.get() != nullptr)
			// to force initialisation at the beginning
			//
			if (instance_.get() == nullptr) {
				Init();
			}
			return instance_.get();
		}

	private:
		static std::unique_ptr<T> instance_;
	};

	template<typename T>
	std::unique_ptr<T> ESingleton<T>::instance_;

}