#include "hashtbl.h"

using namespace MyHashTable;

template< class KeyType, class DataType >
HashTbl<KeyType,DataType>::HashTbl( int TableSz_ )
{
	m_size = TableSz_;
	m_data_table = new list(m_size);
}