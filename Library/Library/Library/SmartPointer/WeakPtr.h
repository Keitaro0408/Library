#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include "SharedPtr.h"
#include "SmartPointer.h"

namespace Lib
{
	template<typename Type>
	class Weak
	{
		friend Shared<Type>;
	public:
		Weak();
		virtual ~Weak();

		/**
		 * ポインタが存在しているか?
		 */
		bool IsExist();

		Weak& operator=(const Shared<Type>&);

	private:
		unsigned int* m_pRefCount;
		unsigned int* m_pWeakCount;
		Type* m_pInstance;
	};

#include "WeakPtr_private.h"
}


#endif
