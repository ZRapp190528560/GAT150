#pragma once
#include <functional>
#include <map>

namespace AZ {
	template <typename Tbase>
	class creatorBase {
	public:
		virtual Tbase* create() const = 0;
	};

	template <typename T, typename Tbase>
	class creator : public creatorBase<Tbase> {
	public:
		virtual Tbase* create() const override { return new T; }
	};

	template <typename Tbase>
	class prototype : public creatorBase<Tbase> {
	public:
		prototype(Tbase* instance) : m_instance{ instance } {}
		Tbase* create() const override { return m_instance->clone(); }

	private:
		Tbase* m_instance{ nullptr };
	};

	template <typename TBase, typename TKey>
	class factory {
	public:
		template <typename T = TBase>
		T* create(TKey key);
		void f_register(TKey key, creatorBase<TBase>* creator);

	protected:
		std::map<TKey, creatorBase<TBase>*> m_registry;
	};

	template <typename TBase, typename TKey>
	template <typename T>
	inline T* factory<TBase, TKey>::create(TKey key) {
		T* object{ nullptr };
		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			creatorBase<TBase>* creator = iter->second;
			object = dynamic_cast<T*>(creator->create());
		}
		return object;
	}

	template <typename TBase, typename TKey>
	inline void factory<TBase, TKey>::f_register(TKey key, creatorBase<TBase>* creator) {
		m_registry[key] = creator;
	}
}