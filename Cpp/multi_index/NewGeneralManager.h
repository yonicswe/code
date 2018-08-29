#pragma once

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <stdint.h>
#include <iostream>

using namespace std;
using namespace boost::multi_index;

template<class PElement>
struct NewGeneralElement
{
    uint64_t    element_time;
    std::string element_name;
    PElement    element;

    NewGeneralElement(uint64_t etime, std::string ename, PElement e)
        : element_time(etime)
        , element_name(ename)
        , element(e)
    {}
};

template<class PGeneralElement>
class NewGeneralManager
{
    public:
        NewGeneralManager(const uint64_t timeout)
            : timeout_(timeout)
        {}
	    void InsertNewElement(PGeneralElement NewElement, const uint64_t ElementTime, std::string ElementName)
        {
            elements_.insert(Element(ElementTime, ElementName, NewElement));
        }
	    void RemoveElement(std::string ElementName)
        {
            typename ElementSetByName::iterator it = elements_.get<1>().find(ElementName);
            if (it != elements_.get<1>().end())
                { elements_.get<1>().erase(it); }
        }
        PGeneralElement find(std::string element_name)
        {
            PGeneralElement e;
            typename ElementSetByName::iterator it = elements_.get<1>().find(element_name);
            if (it != elements_.get<1>().end())
            { e = it->element; }
            return e;
        }
	    void UpdateElementTimeout(std::string ElementName, const uint64_t ElementTime)
        {
            typename ElementSetByName::iterator it = elements_.get<1>().find(ElementName);
            if (it != elements_.get<1>().end())
            {
                Element updated_element = *it;
                updated_element.element_time = ElementTime;
                elements_.get<1>().replace(it, updated_element);
            }
        }
        void flush(uint64_t flush_time)
        {
            if (flush_time == 0)
                { flush_time = getCurrentTime(); }

            elements_.erase(elements_.begin(), elements_.upper_bound(flush_time));
        }
	    void timer(const uint64_t current_time)
        { flush(current_time - timeout_); }
        void clear()
        { flush(0); }
        int size()
        { return elements_.size(); }
	    void print()
        {
            typename ElementSetById::iterator it = elements_.get<0>().begin();
            typename ElementSetById::iterator endit = elements_.get<0>().end();
            for (;it != endit; it++)
                { cout << it->element_time << "," << it->element_name << endl; }
        }

    private:
        typedef NewGeneralElement<PGeneralElement> Element;
        typedef boost::multi_index_container<
            Element,
            indexed_by<
                ordered_non_unique<member<Element, uint64_t ,&Element::element_time> >,
                ordered_unique<member<Element, std::string ,&Element::element_name>
                >
            >
        > ElementSet;
        typedef typename ElementSet::template nth_index<0>::type ElementSetById;
        typedef typename ElementSet::template nth_index<1>::type ElementSetByName;

        uint64_t getCurrentTime()
        {
            time_t current_time;
            time(&current_time);
            return current_time;
        }

        ElementSet elements_;
        const uint64_t timeout_;
};

