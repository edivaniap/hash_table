/**  
 * @file hashtbl.cpp  
 * @version 1.0  
 * @date 14/06/2017  
 * @author Edivânia Pontes de Oliveira  
 * @title Driver program 
 * @brief Contém os testes da Hash Table.  
 */


#include <iostream>
#include <functional>
#include <tuple>
#include <cassert>

#include "hashtbl.h"

using namespace MyHashTable;

// Tipo conta-corrente.
struct Account
{
    //=== Public members
    std::string m_client_name;
    int m_bank_code;
    int m_branch_code;
    int m_acc_number;
    float m_balance;

    //=== Alias
    typedef int AcctKey;

    //=== Special members
    Account( std::string n_ = "<empty>",
            int bnc_ = 1,       // Banco do Brasil.
            int brc_ = 1668,    // Ag. Campus UFRN
            int nmr_ = 0,       // Numero da conta
            float bal_ = 0.f )  // Saldo
        : m_client_name( n_ ),
        m_bank_code( bnc_ ),
        m_branch_code( brc_ ),
        m_acc_number( nmr_ ),
        m_balance( bal_ )
    { /* Empty */ }

    //=== Public interface
    /// Retorna a chave associada com a conta-corrente (Versao 1).
    AcctKey get_key()
    {
        return m_acc_number;
    }

    // DEBUG: Imprime uma formatacao para a conta-corrente.
    inline friend std::ostream &operator<< ( std::ostream & _os, const Account & _acct )
    {
        _os << "[ Client: <" << _acct.m_client_name <<
            "> Bank: <"   << _acct.m_bank_code <<
            "> Branch: <" << _acct.m_branch_code <<
            "> Number: <" << _acct.m_acc_number <<
            "> Balance: <" << _acct.m_balance << "> ]";
        return _os;
    }
};

/// Functor representando a função de dispersão primátia (fp) para a chave (versão 1).
struct KeyHash
{
    std::size_t operator()( const Account::AcctKey & k_ ) const
    {
        // This is just to debug.
        std::cout << ">>> [KeyHash()]: key = " << std::hash< int >()( k_ ) << std::endl;
        // Calcular o valore de dispersao.
        return std::hash< int >()( k_ );
    }
};

/// Functor representando a comparacao entre chaves (versão 1).
struct KeyEqual
{
	bool operator()( const Account::AcctKey & _lhs, const Account::AcctKey & _rhs ) const
	{
		return ( _lhs == _rhs );
	}
};


int main()
{
    {
    	Account acct("Alex Bastos", 1, 1668, 54321, 1500.f);

    	Account myAccounts[] =
            {
                {"Alex Bastos", 1, 1668, 54321, 1500.f},
                {"Aline Souza", 1, 1668, 45794, 530.f},
                {"Cristiano Ronaldo", 13, 557, 87629, 150000.f},
                {"Jose Lima", 18, 331, 1231, 850.f},
                {"Saulo Cunha", 116, 666, 1, 5490.f}
            };

    	// Cria uma tabela de dispersao com capacidade p 23 elementos
    	HashTbl< Account::AcctKey, Account > contas(21);

        assert( contas.capacity() == 23 );
        assert( contas.count() == 0 );

        contas.insert( myAccounts[2].get_key(), myAccounts[2] );
        contas.insert( myAccounts[0].get_key(), myAccounts[0] );
        contas.insert( myAccounts[3].get_key(), myAccounts[3] );
        contas.insert( myAccounts[1].get_key(), myAccounts[1] );
        contas.insert( myAccounts[4].get_key(), myAccounts[4] );

    #ifdef _NOT_NOW
        // Em um segundo momento... [OK]
        Account conta1;

        contas.retrieve( myAccounts[2].get_key(), conta1 );
        std::cout << conta1.m_client_name << std::endl;
    #endif

        contas.print();
        assert( contas.count() == 5 );

        std::cout << "\n>>> Deletando conta de Aline...\n";
        if( contas.remove( myAccounts[1].get_key() ) )
            std::cout << "\t>> Removida com sucesso.\n\n";
        else
            std::cout << "\t>> Não foi possivel remover. Conta nao encotrada.\n\n";

        contas.print();
        assert( contas.count() == 4 );

        Account acc1;
        contas.retrieve( myAccounts[3].get_key(),  acc1);
        assert( myAccounts[3].get_key() ==  acc1.get_key() );
        assert( myAccounts[3].m_client_name ==  acc1.m_client_name );
        assert( myAccounts[3].m_branch_code ==  acc1.m_branch_code );

        //myAccounts[2] ja foi removido de contas, entao o retrieve tem que ser false
        assert( contas.retrieve( myAccounts[1].get_key(),  acc1) == false ); 
    }

    // testando numeros primos
    {
        assert( is_prime(13) );
        assert( is_prime(37) );
        assert( is_prime(59) );
        assert( is_prime(67) );
        assert( is_prime(83) );
        assert( is_prime(97) );
        assert( next_prime(9)  == 11 );
        assert( next_prime(55) == 59 );
        assert( next_prime(74) == 79 );
        assert( next_prime(38) == 41 );
    }

    // testando rehash
    {
        std::cout << "\n>> Testando rehash\n";
        Account accs[] =
            {
                {"Luan", 1, 1668, 35412, 1500.f},
                {"Analyce", 1, 1668, 93264, 530.f},
                {"Joao Victor", 13, 557, 12745, 150000.f},
                {"Mara", 18, 331, 27840, 850.f},
                {"Melqui", 116, 666, 65423, 5490.f},
                {"Dhulya", 116, 666, 78452, 5490.f}
            };

        HashTbl< Account::AcctKey, Account > contas(2);

        assert( contas.capacity() == 2 );
        assert( contas.count() == 0 );

        contas.insert( accs[0].get_key(), accs[0] );
        contas.insert( accs[1].get_key(), accs[1] );
        contas.insert( accs[2].get_key(), accs[2] );
        contas.insert( accs[3].get_key(), accs[3] );
        contas.insert( accs[4].get_key(), accs[4] );
        contas.insert( accs[5].get_key(), accs[5] );
        contas.print();

        assert( contas.capacity() == 5 );
        assert( contas.count() == 6 );
    }

    std::cout << "\n\n>>> Normal exiting...\n";
	return EXIT_SUCCESS;
}
