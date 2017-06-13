#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <list>

using namespace std;

namespace MyHashTable {

    template<class KeyType, class DataType>
    class HashEntry
    {
        public:

            KeyType m_key;  // Armazena a chave associada a informcao
            DataType m_data;// A informacao.

            HashEntry( KeyType kt_, DataType dt_ ) : m_key(kt_), m_data(dt_)
            {/*Empty*/}
    };

    template< class KeyType, class DataType >
    class HashTbl
    {
        public:
            typedef HashEntry<KeyType,DataType> Entry;

            HashTbl( int TableSz_ = DEFAULT_SIZE );
            virtual ~HashTbl();

            bool insert( const KeyType &, const DataType &  );
            bool retrieve( const KeyType &, DataType & ) const;
            // bool remove()
            // void clear()
            // bool empty().
            unsigned int count() const { return m_count; }
            void print();

        private:
            void rehash();        //!< Change Hash table size if load factor >1.0
            unsigned int m_size;  //!< Tamanho da tabela.
            unsigned int m_count; //!< Numero de elementos na tabel. 
            std::list< Entry > *m_data_table; //!< Tabela de listas para entradas de tabela.
            // std::unique_ptr< std::forward_list< Entry > [] > m_data_table;
            static const short DEFAULT_SIZE = 11;
    };

} // MyHashTable
#include "hashtbl.cpp"
#endif











