#include "vision_layers.h"

namespace jaffe {

	template class JConvolutionLayer <int>;
	template class JConvolutionLayer <float>;

	template <typename Dtype>
	bool JConvolutionLayer<Dtype>::Init(const vector<string> param){
		SetParam(param);
		return ReadParam();
	}

	template <typename Dtype>
	bool JConvolutionLayer<Dtype>::SetParam(const vector<string> param){
		return m_param->SetParam(param);
	}

	template <typename Dtype>
	bool JConvolutionLayer<Dtype>::ReadParam(){
		return true;
	}

	template <typename Dtype>
	bool JConvolutionLayer<Dtype>::Show(){
		return m_param->Show();
	}

} // namespace jaffe
