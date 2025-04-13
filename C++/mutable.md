const 成员函数中进行加锁和解锁操作:
``` C++
class ThreadSafeData {
private:
    int data;
    // 互斥锁，使用 mutable 修饰
    mutable std::mutex mtx; 

public:
    ThreadSafeData(int val) : data(val) {}

    // 获取数据的 const 成员函数
    int getData() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data;
    }
};

```