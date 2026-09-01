#include "duneanaobj/StandardRecord/StandardRecord.h"
#include "duneanasel/nd/ndlar/Selections.h"

#include <ROOT/RNTupleReader.hxx>
#include "TH1D.h"
#include <TFile.h>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  auto reader = ROOT::RNTupleReader::Open("caf", argv[1]);
  auto srView = reader->GetView<caf::StandardRecord>("rec");

  int allCount = 0;
  int selectedCount = 0;

  for (auto entryId : reader->GetEntryRange()) {
    const auto sr = srView(entryId);
    for (const auto &ixn : sr.common.ixn.dlp) {
      allCount++;
      if (sel::beam::ndlar::numode::ApplySelectionV0p1(ixn)) selectedCount++;
    }
  }

  std::cout << "All interactions: " << allCount << std::endl;
  std::cout << "Selected interactions: " << selectedCount << std::endl;
  std::cout << "Selection efficiency: " << static_cast<double>(selectedCount) / allCount << std::endl;
  return 0;
}
