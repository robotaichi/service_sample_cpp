#include "ros/ros.h" //ROSをc++で使えるようにする
#include "std_msgs/String.h"
#include "service_sample_cpp/service_file.h" //"パッケージ名/拡張子なしsrvファイル名.h"

class Server{ //サーバのクラス
    public: //publicメンバとして関数を定義
        Server();
        bool callback(service_sample_cpp::service_file::Request &req, service_sample_cpp::service_file::Response &res); //コールバック関数の定義（パッケージ名::拡張子なしsrvファイル名::Request、パッケージ名::拡張子なしsrvファイル名::Response）
    private: //privateメンバとして変数を定義
        ros::NodeHandle nh; //ROSと通信するためのノードハンドルの作成
        ros::ServiceServer server; //サーバの定義
};

Server::Server(){
    server = nh.advertiseService("service_name", &Server::callback, this); //サーバのインスタンス生成
}

bool Server::callback(service_sample_cpp::service_file::Request &req, service_sample_cpp::service_file::Response &res){ //リクエストされると呼び出されるコールバック関数の定義
    res.result = req.a + req.b; //クライアントからのリクエスト変数の合計値をsrvファイルで定義したリスポンス変数に代入
    ROS_INFO("%d", res.result); //ログの表示
    return true; //trueを返す
}

int main(int argc, char **argv){ //メイン関数
    ros::init(argc, argv, "server_node"); //ノードの初期化
    Server srv; //クラスのインスタンス生成
    ros::spin(); //終了防止
    return 0; //終了
}