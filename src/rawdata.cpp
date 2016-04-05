// huangshize 2016.03.16
// === rawdata.cpp ===
// SyncedMemory.cppµÄÌæ´ú

#include "rawdata.h"
#include "math_functions.h"

JRawData::~JRawData() {
	if (m_data_ptr && m_own_data)
	{
		freeHost(m_data_ptr);
	}
	
}

void JRawData::NewData()
{
	if (!m_data_ptr)
	{
		mallocHost(&m_data_ptr, m_size);
		jaffe_memset(m_size, 0, m_data_ptr);
		m_own_data = true;
	}
	
}

const void* JRawData::GetData()
{
	NewData();
	return (const void*)m_data_ptr;
}

void* JRawData::GetMutableData()
{
	NewData();
	return m_data_ptr;
}

 void JRawData::SetData(void* data)
{
	if (m_own_data)
	{
		freeHost(m_data_ptr);
	}
	m_data_ptr = data;
	m_own_data = false;
}
