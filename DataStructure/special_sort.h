//
// Created by agno3 on 8/28/19.
//

#ifndef DATASTRUCTURE__SPECIAL_SORT_H_
#define DATASTRUCTURE__SPECIAL_SORT_H_

#include <vector>
#include <string>

namespace xhy {
    using std::vector;
    using std::string;

//超出N*log(N) 下界的特殊排序方法
    class special_sort {
    public:
        //专门排序等长字符串的计数排序法
        static void
        radix_sort(vector<string> &array, string::size_type len) {
            const int BUCKET = 256;
            vector<vector<string>> buckets(BUCKET);
            while (len-- > 0) {
                for (string &s:array)
                    buckets[s[len]].push_back(s);
                int idx = 0;
                for (auto &buck:buckets) {
                    for (string &s:buck)
                        array[idx++] = s;
                    buck.clear();
                }
            }
        }
        /**
         * 第一个没看懂的算法
         * 尽力了,,,
         * @param array
         * @param len
         */
        static void counting_radix_sort(vector<string> &array, int len) {
            const int BUCKETS = 256;
            int N = array.size();
            vector<string> buffer(N);

            vector<string> *in = &array;
            vector<string> *out = &buffer;


            for (int pos = len - 1; pos >= 0; --pos) {


                vector<int> counts(BUCKETS + 1);
                for (int i = 0; i < N; ++i)
                    ++counts[(*in)[i][pos] + 1];
                for (int j = 1; j < BUCKETS; ++j)
                    counts[j] += counts[j - 1];
                for (int k = 0; k < N; ++k)
                    (*out)[counts[(*in)[k][pos]]++] = std::move((*in)[k]);
                std::swap(in, out);
            }
            if (len % 2 == 1)
                for (size_t l = 0; l < array.size(); ++l)
                    (*out)[l] = std::move((*in)[l]);

        }


    };


}
#endif //DATASTRUCTURE__SPECIAL_SORT_H_
