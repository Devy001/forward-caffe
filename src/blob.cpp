// huangshize 2016.03.28
// hsz0405 fix

#include "blob.h"

namespace jaffe{

	template <typename Dtype>
	void JBlob<Dtype>::Reshape(const int num, const int channels, const int height,
		const int width)
	{
		vector<int> shape(4);
		shape[0] = num;
		shape[1] = channels;
		shape[2] = height;
		shape[3] = width;
		Reshape(shape);
	}

	template <typename Dtype>
	void JBlob<Dtype>::Reshape(const vector<int>& shape)
	{
		m_count = 1;
		m_shape.resize(shape.size());
		if (!m_shape_data || m_shape_data->GetSize() < shape.size() * sizeof(int))
		{
			m_shape_data.reset(new JRawData(shape.size() * sizeof(int)));
		}

		int* shape_data = static_cast<int*>(m_shape_data->GetMutableData());
		for (int i = 0; i < shape.size(); i++)
		{
			m_count *= shape[i];
			m_shape[i] = shape[i];
			shape_data[i] = shape[i];  // 不懂
		}
		// 有待测试
		if (m_count > m_capacity)
		{
			m_data.reset(new JRawData(m_capacity * sizeof(Dtype)));
			m_diff.reset(new JRawData(m_capacity * sizeof(Dtype)));
		}
	}
	// 构造函数
	template <typename Dtype>
	JBlob<Dtype>::JBlob(const int num, const int channels, const int height,
		const int width) : m_capacity(0)
	{
		Reshape(num, channels, height, width);
	}

	template <typename Dtype>
	JBlob<Dtype>::JBlob(const vector<int>& shape) : m_capacity(0)
	{
		Reshape(shape);
	}

	//
	template <typename Dtype>
	const Dtype* JBlob<Dtype>::Data() const
	{
		return (const Dtype*)m_data->GetData();
	}

	template <typename Dtype>
	const Dtype* JBlob<Dtype>::Diff() const
	{
		return (const Dtype*)m_diff->GetData();
	}

	template <typename Dtype>
	Dtype* JBlob<Dtype>::MutableData()
	{
		return static_cast<Dtype*>(m_data->GetMutableData());
	}

	template <typename Dtype>
	Dtype* JBlob<Dtype>::MutableDiff()
	{
		return static_cast<Dtype*>(m_diff->GetMutableData());
	}

	template <typename Dtype>
	void JBlob<Dtype>::SetData(Dtype* data)
	{
		m_data->SetData(data);
	}

	template <typename Dtype>
	void JBlob<Dtype>::ShareData(const JBlob& other)
	{
		// 需要判断两个JBlob的数据大小是否一致
		m_data = other.GetBlobData();
	}
	template <typename Dtype>
	void JBlob<Dtype>::ShareDiff(const JBlob& other)
	{
		m_diff = other.GetBlobDiff();
	}
	//
	// void Updata();

	//
	template <typename Dtype>
	Dtype JBlob<Dtype>::AsumData() const
	{
		if (!m_data) { return 0; }
		if (!m_data->GetOwnData()) { return 0; }
		return jaffe_asum(m_count, Data());  // 未完成
	}

	template <typename Dtype>
	Dtype JBlob<Dtype>::AsumDiff() const
	{
		if (!m_diff) { return 0; }
		// if (!m_diff->GetOwnData()) { return 0; }
		return jaffe_asum(m_count, Diff());  // 未完成
	}


	template <typename Dtype>
	Dtype JBlob<Dtype>::SumsqData() const
	{
		const Dtype* data;
		if (!m_data) { return 0; }
		// if (!m_data->GetOwnData()) { return 0; }
		data = Data();
		return jaffe_dot(m_count, data, data);
	}
	template <typename Dtype>
	Dtype JBlob<Dtype>::SumsqDiff() const
	{
		const Dtype* diff;
		if (!m_diff) { return 0; }
		// if (!m_diff->GetOwnData()) { return 0; }
		diff = Diff();
		return jaffe_dot(m_count, diff, diff);
	}
	
	template <typename Dtype>
	void JBlob<Dtype>::Update()
	{
		jaffe_axpy<Dtype>(m_count, Dtype(-1),
			static_cast<const Dtype*>(m_diff->GetData()),
			static_cast<Dtype*>(m_data->GetMutableData()));
	}

	template <typename Dtype>
	void JBlob<Dtype>::scale_data(Dtype scale_factor)
	{
		if (!m_data)
		{
			return;
		}
		Dtype* data;
		data = MutableData();
		jaffe_scale(m_count, scale_factor, data);

	}
	template <typename Dtype>
	void JBlob<Dtype>::scale_diff(Dtype scale_factor)
	{
		if (!m_diff)
		{
			return;
		}
		Dtype* diff;
		diff = MutableDiff();
		jaffe_scale(m_count, scale_factor, diff);
	}
}
