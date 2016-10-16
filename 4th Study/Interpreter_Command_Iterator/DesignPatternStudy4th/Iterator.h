#pragma once

template <typename T>
class ListIterator
{
public:
	ListIterator( T* listElement ) : m_ListElement( listElement ) {	}

	typename T::value_type& operator*( ) const
	{
		return m_ListElement->m_value;
	}

	typename T::value_type* operator->( ) const
	{
		return &m_ListElement->m_value;
	}

	bool operator==( const ListIterator<T>& rhs ) const
	{
		return m_ListElement == rhs.m_ListElement;
	}

	bool operator!=( const ListIterator<T>& rhs ) const
	{
		return !(*this == rhs);
	}

	ListIterator<T> operator++( )
	{
		m_ListElement = m_ListElement->m_next;
		return (*this);
	}

	T* MyNode( ) const
	{
		return m_ListElement;
	}

private:
	T* m_ListElement;
};