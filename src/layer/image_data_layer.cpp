// huangshize 2016.04.05
// �ӿڲ�����ϸ��δ����ʵ��
#include "data_layers.h"
#include "io.h"

//namespace jaffe {
//
//	template <typename Dtype>
//	void JImageDataLayer<Dtype>::DataLayerSetUp(const vector<JBlob<Dtype>*>& bottom,
//		const vector<JBlob<Dtype>* >& top)
//	{
//		// ����JBaseFetchingDataLayer�ĺ���
//		LayerSetUp(bottom, top);
//
//		// �����ٶ��ļ�·������m_source�������ʵ��
//
//		// ʵ�����ݲ����
//		int new_height;
//		int new_width;
//		// const int new_height = this->m_param.image_data_param().new_height();
//		// const int new_width = this->m_param.image_data_param().new_width();
//
//		m_lines.push_back(make_pair("...", 1));
//		m_lines_id = 0;
//
//		JDatum datum;
//		ReadImageToDatum(m_lines[m_lines_id].first, m_lines[m_lines_id].second,
//			new_height, new_width);
//
//		// (*top)[0]ָ�����bolb
//		// �˴����ȳ�ʼ��blob�ĳߴ�
//		(*top)[0]->Reshape(1, datum.GetChannels(), datum.GetHeight, datum.GetWidth());
//		m_data->Reshape(1, datum.GetChannels(), datum.GetHeight, datum.GetWidth());
//
//		// label
//		(*top)[1]->Reshape(1, 1, 1, 1);
//		m_label ->Reshape(1, 1, 1, 1);
//
//
//	}
//
//	template <typename Dtype>
//	void JImageDataLayer<Dtype>::FetchData()
//	{
//		Dtype* top_data = m_data.MutableData();
//		Dtype* top_label = m_label.MutableData();
//
//		// ����ImageDataLayer�Ĳ���
//		//ImageDataParameter image_data_param = this->layer_param_.image_data_param();
//		const int new_height = image_data_param.new_height();
//		const int new_width = image_data_param.new_width();
//
//		JDatum datum;
//		ReadImageToDatum(m_lines[m_lines_id].first, m_lines[m_lines_id].second,
//			new_height, new_width, datum);
//
//		string img_data = datum.GetData();
//		int size = datum.GetHeight() * datum.GetWidth();
//
//		for (int i = 0; i < size; i++)
//		{
//			Dtype datum_element =
//				static_cast<Dtype>(static_cast<uint8_t>(img_data[i]));
//			top_data[i] = datum_element;
//		}
//
//		top_label[i] = datum.GetLabel();
//
//	}
//
//
//}