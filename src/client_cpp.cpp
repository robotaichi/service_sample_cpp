#include "ros/ros.h" //ROSをc++で使えるようにする
#include "std_msgs/String.h"
#include "service_sample_cpp/service_file.h" //"パッケージ名/拡張子なしsrvファイル名.h"

class Client{ //クライアントのクラス
    public: //publicメンバとして関数を定義
        Client();
        void request(void);
    private: //privateメンバとして変数を定義
        ros::NodeHandle nh; //ROSと通信するためのノードハンドルの作成
        ros::ServiceClient client; //クライアントの定義
        service_sample_cpp::service_file service_message; //サービスメッセージのインスタンス生成
};

Client::Client(){
    client = nh.serviceClient<service_sample_cpp::service_file>("service_name"); //クライアントのインスタンス生成
}

void Client::request(void){
    service_message.request.a = 10; //srvファイルで定義したリクエスト変数に代入
    service_message.request.b = 5; //srvファイルで定義したリクエスト変数に代入

    if (client.call(service_message)){ //サーバと接続ができた場合
        ROS_INFO("%d + %d", service_message.request.a, service_message.request.b); //ログの表示
    }
    else{ //サーバと接続ができなかった場合
        ROS_ERROR("Failed to connect server"); //ログの表示
    }
}


int main(int argc, char **argv){ //メイン関数
    ros::init(argc, argv, "client_node"); //ノードの初期化
    Client cli; //クラスのインスタンス生成
    cli.request(); //クラス内の関数にアクセス（実行）
    ros::spin(); //終了防止
    return 0; //終了
}