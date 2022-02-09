std::list<EdgeResultData> results_list;
std::vector<EdgeResultData> results;
//滚动显示识别结果
        if (!results.empty()){
          for (int n = 0; n < results.size(); n++){
            if (results_list.size() < 5){
              results_list.push_back(results[n]);
            }
            else {
              results_list.pop_front();
              results_list.push_back(results[n]);
            }  
          }
          

          int k = 0;
          for (std::list<EdgeResultData>::iterator it = results_list.begin(); it != results_list.end(); it++){
            //置信度保留两位小数
            ss << std::fixed << std::setprecision(2) << (*it).prob; 
            ss >> prob;
            prob = prob.substr(0,4);
            
            cv::putText(background_temp, (*it).label, cv::Point(200,300 + k *90),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 1, 5);
            cv::putText(background_temp,"p: " + prob, cv::Point(200,340 + k *90),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 1, 5);
            k = k + 1;
          }
          
        }
        else 
        {
          if (!results_list.empty()) {
            int j = 0;
            for (std::list<EdgeResultData>::iterator item = results_list.begin(); item != results_list.end(); item++){
              //置信度保留两位小数
              ss << std::fixed << std::setprecision(2) << (*item).prob; 
              ss >> prob;
              prob = prob.substr(0,4);
              
              cv::putText(background_temp, (*item).label, cv::Point(200,300 + j *90),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 1, 5);
              cv::putText(background_temp,"p: " + prob, cv::Point(200,340 + j *90),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 1, 5);
              j = j + 1;
            }
          }
        }