// Histo.h -- Histogram file header           <by CWR Campbell>
//
// This software is copyrighted © 2003 - 2020 by Codecraft, Inc.
//
// The following terms apply to all files associated with the software
// unless explicitly disclaimed in individual files.
//
// The authors hereby grant permission to use, copy, modify, distribute,
// and license this software and its documentation for any purpose, provided
// that existing copyright notices are retained in all copies and that this
// notice is included verbatim in any distributions. No written agreement,
// license, or royalty fee is required for any of the authorized uses.
// Modifications to this software may be copyrighted by their authors
// and need not follow the licensing terms described here, provided that
// the new terms are clearly indicated on the first page of each file where
// they apply.
//
// IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY
// FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
// ARISING OUT OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY
// DERIVATIVES THEREOF, EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE
// IS PROVIDED ON AN "AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE
// NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
// MODIFICATIONS.
//
// GOVERNMENT USE: If you are acquiring this software on behalf of the
// U.S. government, the Government shall have only "Restricted Rights"
// in the software and related documentation as defined in the Federal
// Acquisition Regulations (FARs) in Clause 52.227.19 (c) (2).  If you
// are acquiring the software on behalf of the Department of Defense, the
// software shall be classified as "Commercial Computer Software" and the
// Government shall have only "Restricted Rights" as defined in Clause
// 252.227-7014 (b) (3) of DFARs.  Notwithstanding the foregoing, the
// authors grant the U.S. Government and others acting in its behalf
// permission to use and distribute the software in accordance with the
// terms specified in this license.

#if ! defined __HISTO_H
#define __HISTO_H

#include <iostream>

// How many indices where value is Over.
#define OVERN_TRACE_COUNT 10

class Histogram {
  public:
   // Standard constructor, defines the range and resolution of the distribution.
   Histogram( unsigned int min, unsigned int countsPer, int bins = 10 ) ;

   // (Virtual) destructor releases dynamic storage for all bins.
   virtual ~Histogram() ;

   // Function to reset a distribution to its empty state.
   void Reset() ;

   // Function to add another data point to the existing distribution.
   void Add( unsigned int data ) ;

   // Access function returning the number of values that have been added.
   unsigned int NValues( ) const { return n ; }

   // Access function returning the minimum value that has been added.
   unsigned int MinValue( ) const { return minData ; }

   // Access function returning the maximum value that has been added.
   unsigned int MaxValue( ) const { return maxData ; }

   // Access function returning the minimum bin.
   unsigned int MinBin( ) const { return minBin ; }

   // Access function returning the counts per bin.
   unsigned int CountsPerBin( ) const { return countsPerBin ; }

   // Access function returning the number of bins.
   int NBins( ) const { return nBins ; }

   // Function returning the mean (average) of all values added.  This value may
   // be subject to numerical imprecision - the accumulation sum is held in a
   // double size floating point variable.
   double MeanValue( ) const ;

   // Access function returning the number of data points that have accumulated
   // in a specific bin.  Bin 0 is the under range bin.  Bin N + 1 is the over
   // range bin, where N is the number of bins specified during creation.
   unsigned int BinCount( int binNumber ) const ;

   // Access function returning the largest number of data points that have been
   // accumulated into any single bin.
   unsigned int MaxBinCount( ) const { return maxFreq ; }

   // Function to display the distribution, one bin per line, in the form
   // "<bin #>, <counts> \n".
   // void Display( ostream & ) const;

  protected:
   // This is a (static) array of indices whose values go into nBins + 1 ("Over").
   // Only OVERN_TRACE_COUNT entries are tracked.
   unsigned int overN[OVERN_TRACE_COUNT] ;

   // This is a (static) array of values corresponding to the above indices.
   // Only OVERN_TRACE_COUNT entries are tracked.
   unsigned int overValueN[OVERN_TRACE_COUNT] ;

   // This is a (static) array of timestamps corresponding to the above indices.
   // Only OVERN_TRACE_COUNT entries are tracked.
   unsigned int overTSN[OVERN_TRACE_COUNT] ;

  private:
   // Number of counts per bin, defines resolution of the binning process.
   unsigned int countsPerBin ;

   // Number of bins in the distribution, defines the binned range.  Two extra
   // slots are allocated to count under and over range data points
   unsigned int nBins ;

   // This variable holds the minimum bound of the first bin.  All data points
   // below are binned as under range.
   unsigned int minBin ;

   // These variables hold the min and max data points that have been added.
   unsigned int minData, maxData ;

   // This variable holds the largest bin count of the histogram.
   unsigned int maxFreq ;

   // This variable holds the number of data points that have been added.
   unsigned int n ;

   // This variable accumulates the total sum of all data points, to calculate
   // the mean value.
   double summation ;

   // This is a pointer to the dynamically allocated bin array.
   unsigned int *binVector ;

   // Pointer to a surrounding guard area for binVector.
   unsigned int *binVectorArea ;
};

#endif
