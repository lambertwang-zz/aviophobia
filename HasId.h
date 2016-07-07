#pragma once
#ifndef __HASID_H__
#define __HASID_H__

namespace av {

    class HasId {
    private:
        // The unique object identifier
        // The id is not allowed to be set. Setting it can and will screw
        // with insertion and removal from ObjectLists because they store
        // Objects ordered by id.
        int id;
        // For maintaining a unique id for each object
        static int id_iterator;
    public:
        // Constructor for the object.
        HasId();

        // Gets the object's id
        int getId() const;
    };
} // End of namespace

#endif // __HASID_H__
