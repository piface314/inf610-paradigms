#ifndef UTILS_H
#define UTILS_H

#define PRINT_A(A,N) {std::cout<<'[';for(size_t i=0;i<N;++i)std::cout<<(i?",":"")<<A[i];std::cout<<']'<<std::endl;}
#define PRINT_V(V) {std::cout<<'[';for(auto it=V.begin();it!=V.end();++it)std::cout<<(it!=V.begin()?",":"")<<*it;std::cout<<']'<<std::endl;}
#define PRINT_M(A,M,N) {std::cout << "\u23A1"; \
    for (size_t i = 0; i < M; ++i) { \
        std::cout << (i ? " " : "") << " "; \
        for (size_t j = 0; j < N; ++j) \
            std::cout << A[N*i + j] << " "; \
        if (i + 1 == M) std::cout << "\u23A6"; \
        std::cout << "\n"; \
    }}


template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> &p) {
    return os << '<' << p.first << ',' << p.second << '>';
}

#endif