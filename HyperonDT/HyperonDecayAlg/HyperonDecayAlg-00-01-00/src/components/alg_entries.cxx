#include "GaudiKernel/DeclareFactoryEntries.h"
#include "HyperonDecayAlg/HyperonDecayAlg.h"
#include "HyperonDecayAlg/Xi0Alg.h"

DECLARE_ALGORITHM_FACTORY( HyperonDecayAlg )
DECLARE_ALGORITHM_FACTORY( Xi0Alg )

DECLARE_FACTORY_ENTRIES( HyperonDecayAlg ) {
  DECLARE_ALGORITHM(HyperonDecayAlg)
}


