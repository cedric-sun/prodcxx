#include <chrono>
#include <iostream>

class Timer
{
    using clk = std::chrono::steady_clock;
    using microseconds = std::chrono::microseconds;

    clk::time_point tsb;
    clk::time_point tse;

public:

    void clear() { tsb = tse = clk::now(); }
    void start() { tsb = clk::now(); }
    void stop() { tse = clk::now(); }

    friend std::ostream& operator<<(std::ostream& o, const Timer& timer)
    {
        return o << timer.secs();
    }

    // return time difference in seconds
    double secs() const
    {
        if(tse <= tsb)
            return 0.0;
        auto d = std::chrono::duration_cast<microseconds>(tse - tsb);
        return d.count() / 1000000.0;
    }
};

static int mod(int a, int b)
{
    int tmp=a/b;
    return a-(b*tmp);
}

static int fast_mod(const int input, const int ceil) {
    // apply the modulo operator only when needed
    // (i.e. when the input is greater than the ceiling)
    return input < ceil ? input : input % ceil;
    // NB: the assumption here is that the numbers are positive
}

int main()
{
    auto N = 1000000000U;
    unsigned sum = 0;

    Timer timer;

    for(auto times = 0U; times < 3; ++times)
    {
        std::cout << "     run: " << (times + 1) << '\n';

        sum = 0;
        timer.start();
        for(decltype(N) n = 0; n < N; ++n)
            sum += n % (N - n);
        timer.stop();

        std::cout << "       %: " << sum << " " << timer << "s" << '\n';

        sum = 0;
        timer.start();
        for(decltype(N) n = 0; n < N; ++n)
            sum += mod(n, N - n);
        timer.stop();

        std::cout << "     mod: " << sum << " " << timer << "s" << '\n';

        sum = 0;
        timer.start();
        for(decltype(N) n = 0; n < N; ++n)
            sum += fast_mod(n, N - n);
        timer.stop();

        std::cout << "fast_mod: " << sum << " " << timer << "s" << '\n';
    }
}
