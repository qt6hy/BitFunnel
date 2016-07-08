#pragma once

#include "BitFunnel/IEnumerator.h"        // TermInfo inherits from IEnumerator.
#include "BitFunnel/ITermTable.h"         // Embeds ITermTable::TermKind.
#include "BitFunnel/Index/IFactSet.h"           // FactHandle is used as a parameter.
#include "BitFunnel/NonCopyable.h"        // TermInfo inherits from NonCopyable.
#include "Term.h"               // Embeds Term::Hash.


namespace BitFunnel
{
    class RowId;
    class TermInfo;

    //*************************************************************************
    //
    // TermInfo
    //
    // TermInfo enumerates the RowIds associated with a Term. TermInfo works
    // closely with TermTable and PackedTermTable to enumerate RowIds.
    //
    //*************************************************************************
    class TermInfo : public IEnumerator<RowId>, NonCopyable
    {
    public:
        // Constructs a TermInfo for a specified hash, based on information in
        // the supplied ITermTable.
        TermInfo(Term const& term, ITermTable const & termTable);

        // Constructs a TermInfo for a fact based on information in the
        // supplied ITermTable.
        TermInfo(FactHandle fact,  ITermTable const & termTable);

        // Returns true if there are no associated RowIds.
        bool IsEmpty() const;

        // IEnumerator methods.
        bool MoveNext();
        void Reset();
        RowId Current() const;

    private:

        // Initializes TermInfo based on the PackedTermInfo returned from the
        // ITermTable.
        void Initialize(PackedTermInfo const & info);

        // The term's hash is used as a seed for adhoc row enumeration.
        // For non-adhoc terms this value is not applicable and is undefined.
        Term::Hash m_hash;

        // Storing ITermTable as a pointer, rather than a reference to
        // allow for assignment operator.
        const ITermTable& m_termTable;

        // Slot index for first RowId.
        unsigned m_rowIdStart;

        // Number of RowId to be enumerated.
        unsigned m_rowIdCount;

        // Stores what kind of the term this TermInfo is for.
        ITermTable::TermKind m_termKind;

        // Using int, rather than unsigned to allow for -1 sentinal for
        // position before start of enumerator.
        int m_currentRow;
    };
}
