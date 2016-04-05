#include "data_layers.h"

namespace jaffe {

	template class JDataLayer <int>;
	template class JDataLayer <float>;

	template <typename Dtype>
	bool JDataLayer<Dtype>::Init(const vector<string> param){
		return m_param->SetParam(param);
	}

	template <typename Dtype>
	bool JDataLayer<Dtype>::Show(){
		return m_param->Show();
	}


} // namespace jaffe