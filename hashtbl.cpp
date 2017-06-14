#include "hashtbl.h"
#include <math.h>

using namespace MyHashTable;

template< class KeyType, class DataType >
HashTbl<KeyType, DataType>::HashTbl ( int TableSz_ )
{
	m_size = next_prime( TableSz_ );
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
bool HashTbl< KeyType, DataType>::insert( const KeyType & key, const DataType & data )
{
    std::hash<KeyType> hashing; //<! função de dispersão
    std::equal_to<KeyType> is_equal; //<! função de comparação    
    
    HashEntry<KeyType, DataType > new_hash_entry(key, data);

    if(m_data_table[hashing(key) % m_size].empty()) { 
        auto i = m_data_table[hashing( key ) % m_size].begin(); 
        for(size_t j = 0u; j < m_data_table[hashing( key ) % m_size].size(); j++) 
        { 
            Entry temp = *i; 
            
            if( is_equal( temp.m_key, key ) )
            { 
                temp.m_data = data; 
                return false;
            }
            i++;
        }
    }

    m_data_table[hashing(key) % m_size].push_back(new_hash_entry); 
    m_count++;
    
    return true; 
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
bool HashTbl< KeyType, DataType >::empty( void ) const
{
    return m_size == 0;
}

template< class KeyType, class DataType >
void HashTbl< KeyType, DataType >::print( void ) const
{
    std::hash<KeyType> hashing;

    for( auto i = 0u; i < m_size; ++i )
    {
        std::cout << i << " :{ key = ";
        for( auto & e : m_data_table[i] )
            std::cout << hashing( e.m_key ) << " ; " << e.m_data << " " ;

        std::cout << " }\n";
    }
}

// ------------ FIND NEXT PRIME NUMBER ------------- //

bool is_prime( long x )
{  
    if( x == 1 ) // 1 é caso especial, e não é primo
        return false;

    // sabemos que o 1 é divisor de todos os números, podemos começar a procurar no dois
    // basta percorrer a lista até x/2. O máximo divisor que um número tem, sem ser ele próprio é a sua metade.
    for( long i = 2; i <= (int) sqrt(x); i++ )
        if( ( x % i ) == 0 )
            return false; //Assim que encontra um divisor, sabe que o número não é primo

    return true; //não encontrou divisores, o número é primo
 }

size_t next_prime( size_t n )
{
	while( true )
	{
		if( is_prime( n ) )
			return n;

		n++;
	}
}