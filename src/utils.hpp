#ifndef UTILS_H
#define UTILS_H

#define PRINT_A(A,N) {std::cout<<'[';for(size_t i=0;i<N;++i)std::cout<<(i?",":"")<<A[i];std::cout<<']'<<std::endl;}
#define PRINT_V(V) {std::cout<<'[';for(auto it=V.begin();it!=V.end();++it)std::cout<<(it!=V.begin()?",":"")<<*it;std::cout<<']'<<std::endl;}

template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> &p) {
    return os << '<' << p.first << ',' << p.second << '>';
}

#endif