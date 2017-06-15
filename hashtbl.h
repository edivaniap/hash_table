#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <list>

using namespace std;

bool is_prime( int );
size_t next_prime( int );

namespace MyHashTable {

    template<class KeyType, class DataType>
    class HashEntry
    {
        public:

            KeyType m_key;   //<! Armazena a chave associada a informção.
            DataType m_data; //<! A informação.

            HashEntry( KeyType kt_, DataType dt_ ) : m_key(kt_), m_data(dt_)
            { /* empty */ }
    };

    template< class KeyType, class DataType >
    class HashTbl
    {
        public:
            typedef HashEntry<KeyType,DataType> Entry;

            /*! @brief Construtor que aloca dinamicamente em *m_data_table um vetor cujo tamanho é determinado como sendo
                o menor número primo maior ou igual do que o valor especificado em TableSz_ .*/
            HashTbl( int TableSz_ = DEFAULT_SIZE ); //done

            /*! @brief Destruidor da classe que libera a memória apontada por m_data_table.*/
            virtual ~HashTbl( void ); //done

            /*! @brief Insere na tabela a informação contida em d_ e associada a uma chave k_.
                A classe calcula o endereço 'indice' que a informação d_ deve ocupar na tabela e o armazena na
                lista de colisão correspondente, ou seja, em m_data_table[indice] . Se a inserção foi realizada
                com sucesso a função retorna true. Se a chave já existir na tabela, o método sobrescreve
                os dados da tabela com os dados contidos em d_ e retorna "false", para diferenciar de uma
                inserção realizada pela primeira vez. */
            bool insert( const KeyType & k_, const DataType & d_ ); //done

            /*! @brief Recupera em d_ a informação associada a chave k_ passada como argumento para o método. 
                Se a chave for encontrada o método retorna "true", caso contrário "false".*/
            bool retrieve( const KeyType & k_, DataType & d_ ) const;

            /*! @brief Remove um item de tabela identificado por sua chave k_.
                Se a chave for encontrada o método retorna "true", caso contrário retorna "false". */
            bool remove( const KeyType & k_ );

            /*! @brief Libera toda a memória associada às listas de colisão da tabela, removendo todos seus elementos. */
            void clear( void ); //done

            /*! @brief Retorna "true" se a tabela de dispersão estiver vazia, ou "false" caso contr´ario. */
            bool empty( void ) const; //done

            /*! @brief Retorna a quantidade de elemento atualmente armazenados na tabela. */
            size_t count( void ) const; //done

            /*! @brief Retorna o número de elementos que a tabela suporta. */
            size_t capacity( void ) const; //done
           
            /*! @brief Mostra na tela toda a tabela. */
            void print( void ) const; //done

        private:
            /*! @brief Muda o tamanho da tabela quando o fator de carga (razão entre o número de elementos na tabela e seu tamanho) for maior que 1,0. */
            void rehash();       
            size_t m_size;  //<! Tamanho da tabela.
            size_t m_count; //<! Número de elementos na tabela. 
            std::list< Entry > *m_data_table; //<! Tabela de listas para entradas de tabela.
            static const short DEFAULT_SIZE = 11; //<! tamanho padrão.
    };

} // MyHashTable
#include "hashtbl.cpp"
#endif











