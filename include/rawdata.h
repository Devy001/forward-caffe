// huangshize 2016.03.28
// === rawdata.h ===
// SyncedMemory.hpp������������洢ԭʼ����
// û��ʵ��cpu������gpu���ݵ�ͬ��

#ifndef JAFFE_RAWDATA_H_
#define JAFFE_RAWDATA_H_

#include <cstdlib>
#include "common.h"


// Ϊָ�뿪�ٿռ�
inline void mallocHost(void** ptr, size_t size)
{
	*ptr = malloc(size);
}
// ���տռ�
inline void freeHost(void* ptr)
{
	free(ptr);
}

class JRawData {
public:
	JRawData() : m_data_ptr(NULL), m_size(0), m_own_data(false){}
	JRawData(size_t size) : m_data_ptr(NULL), m_size(size), m_own_data(false) {}
	~JRawData();

	// ����RawData�����ݵĴ�С
	size_t GetSize() { return m_size; }
	//
	bool GetOwnData() { return m_own_data; }
	// ��ȡdata��ָ��
	const void* GetData();
	void* GetMutableData();

	void SetData(void* data);



private:
	void NewData();  // to_cpu() / to_gpu ()

	void* m_data_ptr;
	size_t m_size;
	bool m_own_data;
};

#endif