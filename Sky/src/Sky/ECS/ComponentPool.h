#pragma once
#include <skypch.h>

#include "IComponentPool.h"

namespace Sky
{
	template<typename T>
	class ComponentPool : public IComponentPool
	{
	public:
		template<typename... Args>
		void Add(Entity entity, Args&&... args)
		{
			const auto index = GetEntityIndex(entity);

			if (Has(entity)) {
				m_Dense[m_Sparse[index]] = T{ std::forward<Args>(args)... };
				return;
			}

			if (index >= m_Sparse.size())
				m_Sparse.resize(index + 1, UINT32_MAX);

			m_Dense.emplace_back(std::forward<Args>(args)...);
			m_DenseIds.push_back(entity);
			m_Sparse[index] = m_Dense.size() - 1;
		}

		void Remove(const Entity entity) override
		{
			const auto entIndex = GetEntityIndex(entity);
			const auto index = m_Sparse[entIndex];
			const auto last = m_DenseIds.back();

			m_Dense[index] = m_Dense.back();
			m_DenseIds[index] = last;
			m_Sparse[GetEntityIndex(last)] = index;
			m_Sparse[entIndex] = UINT32_MAX;
			m_Dense.pop_back();
			m_DenseIds.pop_back();
		}

		void SwapToIndex(const Entity entity, size_t index) override
		{
			const auto entIndex = GetEntityIndex(entity);
			const auto currentIndex = m_Sparse[entIndex];

			if (currentIndex == index)
				return;

			const auto swapEntity = m_DenseIds[index];
			std::swap(m_Dense[currentIndex], m_Dense[index]);
			std::swap(m_DenseIds[currentIndex], m_DenseIds[index]);
			m_Sparse[GetEntityIndex(swapEntity)] = currentIndex;
			m_Sparse[entIndex] = index;
		}

		T& Get(const Entity entity)
		{
			SKY_ASSERT(Has(entity), "Entity: {0} does not exist!!!", entity)
			auto componentIndex = m_Sparse[GetEntityIndex(entity)];
			return m_Dense[componentIndex];
		}

		bool Has(const Entity entity) const override
		{
			return GetEntityIndex(entity) < m_Sparse.size() && m_Sparse[GetEntityIndex(entity)] != UINT32_MAX;
		}

		std::vector<T>& GetDense()
		{
			return m_Dense;
		}

		std::vector<Entity>& GetDenseIds() override
		{
			return m_DenseIds;
		}

		size_t Size() const override {
			return m_Dense.size();
		}

		size_t GetIndex(const Entity entity) const override {
			SKY_ASSERT(Has(entity), "Entity: {0} does not exist!!!", entity)
			return m_Sparse[GetEntityIndex(entity)];
		}

	private:
		std::vector<T> m_Dense;
		std::vector<Entity> m_DenseIds; 
		std::vector<uint32_t> m_Sparse;
	};
}
