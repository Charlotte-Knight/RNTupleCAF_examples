#include "duneanaobj/StandardRecord/StandardRecord.h"

#include <ROOT/RNTupleReader.hxx>
#include "TH1D.h"
#include <TFile.h>

constexpr double NDLArXLo = -346.9;
constexpr double NDLArXHi = 346.9;
constexpr double NDLArYLo = -215.5;
constexpr double NDLArYHi = 81.7;
constexpr double NDLArZLo = 418.2;
constexpr double NDLArZHi = 913.3;

bool inFV(caf::SRInteraction ixn) {
  return ixn.vtx.x > NDLArXLo && ixn.vtx.x < NDLArXHi &&
         ixn.vtx.y > NDLArYLo && ixn.vtx.y < NDLArYHi &&
         ixn.vtx.z > NDLArZLo && ixn.vtx.z < NDLArZHi;
}

// check in ixn is in FV and if has primary and if all primaries are contained
bool isSelected(caf::SRInteraction ixn) {
  if (!inFV(ixn)) return false;

  bool hasPrimary = false;
  for (const auto &part : ixn.part.dlp) {
    if (part.primary) {
      hasPrimary = true;
      if (!part.contained) return false;
    }
  }
  return hasPrimary;
}

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
      if (isSelected(ixn)) selectedCount++;
    }
  }

  std::cout << "All interactions: " << allCount << std::endl;
  std::cout << "Selected interactions: " << selectedCount << std::endl;
  std::cout << "Selection efficiency: " << static_cast<double>(selectedCount) / allCount << std::endl;
  return 0;
}
