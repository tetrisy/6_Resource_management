#pragma once

#include <utility>

template <typename Resource>
class SharedPtr
{
private:
	Resource* m_res;
	long* m_counter;
public:
	SharedPtr() {
		m_res = nullptr;
		m_counter = nullptr;
	}

	explicit SharedPtr(Resource* res) {
		if (res != nullptr) {
			m_res = res;
			m_counter = new long(1);
		}
		else {
			m_res = nullptr;
			m_counter = nullptr;
		}
	}

	SharedPtr(const SharedPtr<Resource>& rhs) {
		m_res = rhs.m_res;
		m_counter = rhs.m_counter;

		if (m_counter != nullptr) {
			++(*m_counter);
		}
	}

	SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {
		SharedPtr<Resource> temp(rhs);
		Swap(temp);
		return *this;
	}

	~SharedPtr() {
		if (m_counter != nullptr) {
			--(*m_counter);

			if (*m_counter == 0) {
				delete m_res;
				delete m_counter;
			}
		}
	}

	void Reset() {
		SharedPtr<Resource> temp;
		Swap(temp);
	}

	void Reset(Resource* res) {
		SharedPtr<Resource> temp(res);
		Swap(temp);
	}

	void Swap(SharedPtr<Resource>& rhs) {
		std::swap(m_res, rhs.m_res);
		std::swap(m_counter, rhs.m_counter);
	}

	Resource* Get() const {
		return m_res;
	}

	Resource& operator*() const {
		return *m_res;
	}

	Resource* operator->() const {
		return m_res;
	}

	long UseCount() const {
		if (m_counter != nullptr) {
			return *m_counter;
		}
		else {
			return 0;
		}
	}
};