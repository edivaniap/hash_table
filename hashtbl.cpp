#include "hashtbl.h"

using namespace MyHashTable;

template< class KeyType, class DataType >
HashTbl<KeyType, DataType>::HashTbl ( int TableSz_ )
{
	m_size = TableSz_;
    m_count = 0u;
    m_data_table = new std::list< Entry >[m_size];
}

template< class KeyType, class DataType >
HashTbl< KeyType, DataType>::~HashTbl( void )
{
    clear();
    delete [] m_data_table;
}

template< class KeyType, class DataType >
void HashTbl< KeyType, DataType >::clear( void )
{
    for(size_t i = 0u; i < m_size; i++)
    	m_data_table[i].clear();
    
    m_count = 0;
}

template< class KeyType, class DataType >
size_t HashTbl< KeyType, DataType >::count( void ) const
{
	return m_count;
}

template< class KeyType, class DataType >
size_t HashTbl< KeyType, DataType >::capacity( void ) const
{
	return m_size;
}

template< class KeyType, class DataType >
size_t HashTbl< KeyType, DataType >::empty( void ) const
{
	return m_size == 0;
}