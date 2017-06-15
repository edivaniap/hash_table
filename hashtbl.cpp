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
bool HashTbl< KeyType, DataType>::insert( const KeyType & k_, const DataType & d_ )
{
    //<! se o fator de carga > 1,0 : rehash()
    //if( m_count / m_size > 1.0 ) rehash();

    std::hash<KeyType> hashing; //<! função de dispersão
    std::equal_to<KeyType> is_equal; //<! função de comparação    
    
    HashEntry<KeyType, DataType > new_hash_entry(k_, d_);

    auto indice = hashing(k_) % m_size; //<! calcula o indice 

    /* caso exista elemento no indice calculado */
    if( not m_data_table[indice].empty() )
    { 
        auto it = m_data_table[indice].begin(); //<! iterador auxiliar

        for(size_t j = 0u; j < m_data_table[indice].size(); j++) //<! percorre toda a lista nesta posição da tabela
        {             
            if( is_equal( it->m_key, k_ ) )
            { 
                it->m_data = d_; //<! se for igual, atualiza a informação e retorna false
                return false;
            }

            it++;
        }
    }

    /* caso não exista elemento no indice calculado */
    m_data_table[indice].push_back(new_hash_entry); 
    m_count++;
    
    return true; 
}

template< class KeyType, class DataType >
bool HashTbl< KeyType, DataType>::retrieve( const KeyType & k_, DataType & d_ ) const
{
    return false;
}

template< class KeyType, class DataType >
bool HashTbl< KeyType, DataType>::remove( const KeyType & k_ )
{
    std::hash<KeyType> hashing; 
    std::equal_to<KeyType> is_equal;

    auto indice = hashing( k_ ) % m_size;         

    for(size_t j = 0u; j < m_data_table[indice].size(); j++) //<! percorre toda a lista nesta posição da tabela
    {             
        auto it = m_data_table[indice].begin(); //<! iterador auxiliar
        if( is_equal( it->m_key, k_ ) )
        { 
            m_data_table[indice].erase(it); //<! se for igual, deleta dado
            m_count--;
            return true;
        }

        it++;
    }

    return false; // não encontrou ninguem com a mesma chave
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
        std::cout << i << " : { key = ";
        for( auto & e : m_data_table[i] )
            std::cout << hashing( e.m_key ) << " ; " << e.m_data << " " ;

        std::cout << " }\n";
    }
}

// ------------ find next prime number ------------- //

bool is_prime( int n )
{  
    if( n == 1 ) //<! 1 é caso especial e não é primo
        return false;

    for( int i = 2; i <= (int) sqrt(n); i++ )
        if( ( n % i ) == 0 )
            return false; //<!  Se encontra um divisor de 2 a sqrt(n), sabe-se que o número não é primo.

    return true; //<! Não encontrou divisores, o número é primo.
 }

size_t next_prime( int n )
{
	while( true ) //<! enquanto não achar o próximo primo...
	{
		if( is_prime( n ) )
			return n; 

		n++;
	}
}