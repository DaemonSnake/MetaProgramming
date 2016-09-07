# MetaProgramming
A collection of C++14 Header files for Metaprogramming

For now it allows the following feats:<br>
-Advance index sequence (a more complete std::index_sequence)<br>
-A merge sort utility class that sorts class's template (Holder<5, 8, 1> => Holder<1, 5, 8>)<br>
-A template type remover (removes template argument from a templated class)<br>
-A Compile-time HashMap of values to types (Map::create<>::set<0, void>::get<0> => void)<br>
