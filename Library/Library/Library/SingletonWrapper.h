/**
 * @file   SingletonWrapper.h
 * @brief  SingletonWrapperクラスのヘッダファイル
 * @author kotani
 */
#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H
#include <windows.h>
#define	SINGLETON_CREATE(InstanceType)	 Lib::SingletonWrapper<InstanceType>::Create()
#define	SINGLETON_DELETE(InstanceType)	 Lib::SingletonWrapper<InstanceType>::Delete()
#define	SINGLETON_INSTANCE(InstanceType) Lib::SingletonWrapper<InstanceType>::GetInstance()

namespace Lib
{
	/**
	 * シングルトンクラスを使う際にこいつを使う
	 */
	template <class T> 
	class SingletonWrapper {
	public:
		//typedefをしないとクラステンプレート外からは使えない
		typedef T InstanceType;
		/**
		 * インスタンスを取得する
		 * @return インスタンス
		 */
		inline static InstanceType& GetInstance(){
			return *m_Instance;
		}

		/**
		 * インスタンスを生成する
		 */
		inline static void Create()
		{
			if (m_Instance == NULL)
			{
				m_Instance = new InstanceType;
			}
		}

		/**
		 * インスタンスを破棄する
		 */
		inline static void Delete()
		{
			delete m_Instance;
			m_Instance = NULL;
		}

	private:
		SingletonWrapper(const SingletonWrapper& obj);
		SingletonWrapper& operator=(const SingletonWrapper& obj);

		SingletonWrapper(){};
		virtual ~SingletonWrapper(){};
		static T* m_Instance;

	};

	template <class Type>
	//SingletonWrapper<Type>::InstanceTypeを型と明示的に宣言する
	typename SingletonWrapper<Type>::InstanceType* SingletonWrapper<Type>::m_Instance = NULL;
}

#endif

