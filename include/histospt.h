// histospt.h -- histogram support header file
//
// This software is copyrighted (C) 2003 - 2021 by Codecraft, Inc.
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

#if ! defined __HISTOSPT_H
#define __HISTOSPT_H

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
//#include <string.h>                     // strncpy on Cygwin
#include "histo.h"                      // base class

// Global function to pause and wait for a keystroke.
//void pause( void );

// Display properties.
enum { base10, base16, graph, data };

// A simple class for tallying and displaying interval times.
class TimeIntervalHistogram : Histogram
{
   // Display canvass limits.
   const static int width  = 79;
   const static int height = 58;

   double maxBarSize;                  // 34.0* (half-screen) | 71.0 (full-scrn)
   double mean;
   double convFactor;                  // converts performance counts to µs
   int barChar;                        // 219
   int halfBarChar;                    // 221
   int col;                            // leftmost column of the graph:  1 | 41*
   int col_b;                          // leftmost column of the bars:  col + 7
   int maxCol;                         // col_b + maxBarSize
   int top;                            // top row of the graph:  1
   int bottom;                         // bottom row of the graph:  46
   int displayMode;                    // graph* | data
   bool firstTime;                     // first time switch to trigger some
                                       //   initialization
   struct timeval tvPrevTimeValue;
   struct timeval tvNextTimeValue;
   unsigned int overCount;
   char m_banner[width + 1];           // Histogram top title

   char window[height][width + 1];     // canvass for displaying the histogram

                     // Note: the asterisked values above are not yet supported.

   friend void DisplayHistGraph( TimeIntervalHistogram &dataSet );
   friend void DisplayHistBins( TimeIntervalHistogram &dataSet, int radix );

 public:

   // Standard constructor; defines the ???, range, and resolution of
   // the distribution.
   TimeIntervalHistogram( const char* banner = 0,
                          unsigned int min = 0,
                          unsigned int countsPer = 500,
                          int bins = 40 )
                        : Histogram( min, countsPer, bins ), maxBarSize( 71.0 ),
                          barChar( 219 ), halfBarChar( 221 ),
                          displayMode( data ), firstTime( true ),
                          col( 0 ), col_b( col + 7 ),
                          maxCol( col_b + (int)maxBarSize ),
                          top( 3 ), bottom( height - 13 )
   {
      if ( banner )
      {
         strncpy( m_banner, banner, width ); // protect against an overwrite
         m_banner[width] = '\0';             // insure null termination
      }
   }

   // Destructor releases ??? ???.
   ~TimeIntervalHistogram() { }

   // Add an entry to the time interval histogram, with a value equal to the
   // elapsed time since the previous tally request.  The first tally request
   // does not add an entry; it merely stores an initial time value in
   // preparation for subsequent tally requests.
   void tally( void );

   // Clear the histogram.
   void reset( void );

   // Updates the time interval without adding an entry to the histogram.
   // This allows capturing non-contiguous time intervals for the histogram.
   void restartTimer( void );

   // Show (and optionally log, if the boolean is true,) the histogram
   // and then wait for the user to hit a key.
   void show( bool logToo = false );

   // Add a scalar point (i.e., not a time interval) to the histogram.
   /* This is so I can create and display a normal histogram. CWRC */
   void add( unsigned int data );
};

#endif // ! defined __HISTOSPT_H
