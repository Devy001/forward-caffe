// huangshize 2016.03.28
// huangshize 2016.04.05 bug fixed
#ifndef JAFFE_BLOB_H_
#define JAFFE_BLOB_H_


#include "math_functions.h"
#include "common.h"
#include "rawdata.h"

namespace jaffe {

	template <typename Dtype>
	class JBlob
	{
	public:
		// ���캯��
		JBlob() : m_data(), m_diff(), m_count(0), m_capacity(0) {}
		explicit JBlob(const int num, const int channels, const int height,
			const int width);
		explicit JBlob(const vector<int>& shape);
		// ��������
		~JBlob();

		//  Reshape
		void Reshape(const int num, const int channels, const int height,
			const int width);
		void Reshape(const vector<int>& shape);

		//
		inline const vector<int>& shape() const { return m_shape; }
		// �����index��ά�ȵ�ά����֧��indexС��0���������
		inline int GetShape(int index) const
		{
			return m_shape[CannonicalAxisIndex(index)];
		}
		inline int CannonicalAxisIndex(int axis_index) const
		{
			if (axis_index < 0)
			{
				return axis_index + GetNumAxes();  //hsz0405 bug fixed
			}
			return axis_index;
		}
		// ��ȡ����ָ��ά�ȵ�ά��
		inline int GetNum() const { return GetShape(0); }
		inline int GetChannels() const { return GetShape(1); }
		inline int GetHeight() const { return GetShape(2); }
		inline int GetWidth() const { return GetShape(3); }

		inline int GetNumAxes() const { return m_shape.size(); }
		inline int GetCount() const { return m_count; }
		inline int GetCount(int start_axis, int end_axis) const
		{
			// ��Ҫ�ж�index��Χ
			int count = 1;
			for (int i = start_axis; i < end_axis; i++)
			{
				count *= GetShape(i);
			}
			return count;
		}
		inline int GetCount(int start_axis) const
		{
			// ��Ҫ�ж�index��Χ
			return GetCount(start_axis, GetNumAxes());
		}

		// ���� offset ƫ����
		inline int CalOffset(const int n, const int c = 0, const int h = 0,
			const int w = 0) const
		{
			// ��Ҫ�ж� n c h w �Ĵ�С��û�г�����Χ
			return ((n * GetChannels() + c) * GetHeight() + h) * GetWidth() + w;  // hsz0405 bug fixed
		}

		inline int CalOffset(const vector<int>& indices) const
		{
			int offset = 0;
			for (int i = 0; i < GetNumAxes(); i++)
			{
				offset *= GetShape(i);
				if (indices.size() > i)
				{
					offset += indices[i];  // hsz0405 bug fixed
				}
			}
			return offset;
		}

		void CopyFrom(const JBlob<Dtype>& source, bool copy_diff = false, bool reshape = false);

		// ͨ��offsetƫ�������������
		inline Dtype DataAt(const int n, const int c, const int h, const int w) const
		{
			return Data()[CalOffset(n, c, h, w)]; // hsz0405 bug fixed
		}

		inline Dtype DiffAt(const int n, const int c, const int h, const int w) const
		{
			return Diff()[CalOffset(n, c, h, w)]; // hsz0405 bug fixed
		}

		inline Dtype DataAt(const vector<int>& index) const
		{
			return Data()[CalOffset(index)]; // hsz0405 bug fixed
		}

		inline Dtype DiffAt(const vector<int>& index) const
		{
			return Diff()[CalOffset(index)]; // hsz0405 bug fixed
		}

		inline const shared_ptr<JRawData>& GetBlobData() const
		{
			return m_data;
		}
		inline const shared_ptr<JRawData>& GetBlobDiff() const
		{
			return m_diff;
		}

		//
		const Dtype* Data() const;	// ԭblob.hpp�е�cpu_data() / gpu_data()
		const Dtype* Diff() const;	// ԭblob.hpp�е�cpu_diff() / gpu_diff()
		Dtype* MutableData();
		Dtype* MutableDiff();

		void SetData(Dtype* data);

		void Update();
		// void FromProto(..)
		// void ToProto(..)

		// �ֱ����data��diff�ľ���ֵ֮���Լ�ƽ��֮��
		Dtype AsumData() const;
		Dtype AsumDiff() const;
		Dtype SumsqData() const;
		Dtype SumsqDiff() const;

		// �漰cblas��������
		void scale_data(Dtype scale_factor);
		void scale_diff(Dtype scale_factor);

		//
		void ShareData(const JBlob& other);
		void ShareDiff(const JBlob& other);

		//bool ShapeEquals(const BlobProto& other);

	protected:
		shared_ptr<JRawData> m_data;
		shared_ptr<JRawData> m_diff;
		shared_ptr<JRawData> m_shape_data;
		vector<int> m_shape;
		int m_count;
		int m_capacity;  // ����  ��ʱ����
	private:

	};



}

#endif