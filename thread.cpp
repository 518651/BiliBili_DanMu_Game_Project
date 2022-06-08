#include "Control.h"
#include <vector>
#include <chrono>
#include "ThreadPool.h"

int cnt = 20;
std::mutex thlock;

DanMu_Data DanMu_Data_R;

void Thread_one(string DanMu_Analysis) {
	std::lock_guard<std::mutex> lockGuard(thlock);
	analysis(DanMu_Analysis);
}

int cotrol_Thread(string data) {
    //ThreadPool pool(4);
    //std::vector< std::future<int> > results;

    //for (int i = 0; i < 8; ++i) {
    //    results.emplace_back(
    //        pool.enqueue([i] {
    //            analysis(DanMu_Data_R.LostText);
    //           // std::cout << "hello " << i << std::endl;
    //            //std::this_thread::sleep_for(std::chrono::seconds(1));
    //           // std::cout << "world " << i << std::endl;
    //            return 0;

    //            })
    //    );
    //}

    //for (auto&& result : results)
    //    std::cout << result.get() << ' ';
    //std::cout << std::endl;
    int model;
    model=analysis(data);
    input_funtion(model);

    return 0;
}