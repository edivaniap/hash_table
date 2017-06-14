#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <list>

using namespace std;

bool is_prime( long );
size_t next_prime( size_t );

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

            HashTbl( int TableSz_ = DEFAULT_SIZE ); //done
            virtual ~HashTbl( void ); //done

            bool insert( const KeyType &, const DataType &  );
            bool retrieve( const KeyType &, DataType & ) const;
            // bool remove()
            void clear( void ); //done

            bool empty( void ) const; //done
            size_t count( void ) const; //done
            size_t capacity( void ) const; //done
           
            void print( void ) const; 

        private:
            void rehash();        //!< Change Hash table size if load factor >1.0
            size_t m_size;  //!< Tamanho da tabela.
            size_t m_count; //!< Numero de elementos na tabel. 
            std::list< Entry > *m_data_table; //!< Tabela de listas para entradas de tabela.
            // std::unique_ptr< std::forward_list< Entry > [] > m_data_table;
            static const short DEFAULT_SIZE = 11;
    };

} // MyHashTable
#include "hashtbl.cpp"
#endif











