#pragma once

#include "Iterator.h"

template <typename T>
class ListElement
{
public:
	typedef T value_type;

	ListElement( ) : m_value{}, m_prev( this ), m_next( this ) { }
	ListElement( const T& value ) : m_value( value ), m_prev( this ), m_next( this ) { }
	ListElement( T&& value ) : m_value( std::forward<T>( value ) ), m_prev( this ), m_next( this ) { }

	T m_value;
	ListElement<T>* m_prev;
	ListElement<T>* m_next;
};

template <typename T>
class LinkedList
{
public:
	void push_back( const T& val )
	{
		ListIterator<ListElement<T>> begin( &m_head );
		insert( begin, val );
	}

	void push_back( T&& val )
	{
		ListIterator<ListElement<T>> begin( &m_head );
		insert( begin, std::forward<T>( val ) );
	}

	template <typename U>
	void insert( ListIterator<ListElement<T>> iter, U&& elem )
	{
		ListElement<T>* curNode = iter.MyNode( );
		ListElement<T>* newNode = new ListElement<T>( std::forward<U>( elem ) );
		newNode->m_next = curNode;
		newNode->m_prev = curNode->m_prev;
		++m_size;
		curNode->m_prev = newNode;
		newNode->m_prev->m_next = newNode;
	}

	ListIterator<ListElement<T>> begin( ) noexcept
	{
		return ListIterator<ListElement<T>>( m_head.m_next );
	}

	ListIterator<ListElement<T>> end( ) noexcept
	{
		return ListIterator<ListElement<T>>( &m_head );
	}

	int size( ) const noexcept
	{
		return m_size;
	}

	LinkedList( ) : m_size( 0 )
	{
	}

	~LinkedList( )
	{
		ListElement<T>* node = m_head.m_next;
		m_head.m_prev = &m_head;
		m_head.m_next = &m_head;

		for ( ListElement<T>* next; node != &m_head; node = next )
		{
			next = node->m_next;
			delete node;
		}
	}
private:
	ListElement<T> m_head;
	unsigned int m_size;
};