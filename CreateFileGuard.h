#pragma once

#include <windows.h>

class CreateFileGuard {
private:
	HANDLE m_createFileHandle;
public:
	explicit CreateFileGuard(HANDLE fileHandle) : m_createFileHandle(fileHandle) {}
	CreateFileGuard(const CreateFileGuard& other) = delete;
	CreateFileGuard& operator=(const CreateFileGuard& other) = delete;

	~CreateFileGuard() {
		if (m_createFileHandle != INVALID_HANDLE_VALUE && m_createFileHandle != nullptr) {
			CloseHandle(m_createFileHandle);
		}
	}

	HANDLE getHandle() const {
		return m_createFileHandle;
	}
};