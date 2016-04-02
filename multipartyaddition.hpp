/**
* \file multipartyaddition.hpp
*
* \author Sarah Scheffler and /TODO add yourselves
*
* \brief Do multiparty addition
*/

#ifndef MULTIPARTYADDITION_HPP_INCLUDED
#define MULTIPARTYADDITION_HPP_INCLUDED 1

#include "datamanager.hpp" // for point typedef

/**
* \class MultiPartyAddition
*
* \brief A class for doing the multi-party addition protocol.  HELib will handle the actual
* operations.
*/
class MultiPartyAddition {

public:

	/// Multiplies datafromPreviousClient by E(newData, encKey)
    static unsigned char[] MPAForward(const unsigned char[] dataFromPreviousClient, 
    	const unsigned char[] newData,
    	const unsigned char[] encKey) const;

    /// Returns dataFromSuccessiveClient to the power of the inverse of outputShare
    static unsigned char[] MPABackward(const unsigned char[] dataFromSuccessiveClient,
    	const unsigned char[] outputShare) const;

    /// Function for the server to calculate the last share
    static unsigned char[] getLastShare(const unsigned char[] dataFromSuccessiveClient,
    	const unsigned char[] decKey) const;
};
