#pragma once

#include "vertagt_aktion.h"
#include <list>
#include <algorithm>//find_if


namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default;
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			return p_objekte.empty();
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			auto ptr = std::make_unique<VPushBack<T>>(p_objekte, std::move(obj));
			p_aktionen.push_back(std::move(ptr));
		}

		void push_front(T obj)
		{
			auto ptr = std::make_unique<VPushFront<T>>(p_objekte, std::move(obj));
			p_aktionen.push_front(std::move(ptr));
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			auto ptr = make_unique<VErase<T>>(p_objekte, it);
			p_aktionen.push_back(std::move(ptr));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			while (!p_aktionen.empty())
			{
				// Aktionszeiger auf 1. Element bestimmen und in Liste entfernen
				auto iter = p_aktionen.begin();
				(*iter)->vAusfuehren();
				p_aktionen.erase(iter);
				
				/*std::unique_ptr <VAktion<T>> p_aktion = NULL;
				p_aktion = std::move(*iter);
				p_aktionen.remove(NULL);*/

				// Aktion ausführen
				
			}
		}
	};
} // namespace vertagt
