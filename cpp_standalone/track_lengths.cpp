#include "duneanaobj/StandardRecord/StandardRecord.h"

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

  TH1D *track_lengths = new TH1D("track_lengths", "Track Lengths", 100, 0, 600);

  for (auto entryId : reader->GetEntryRange()) {
    const auto sr = srView(entryId);
    for (const auto &ixn : sr.common.ixn.dlp) {
      for (const auto &part : ixn.part.dlp) {
        track_lengths->Fill((part.end-part.start).Mag()); // ignore showers which go into overflow
      }
    }
  }

  TFile outFile("track_lengths.root", "RECREATE");
  track_lengths->Write();
  outFile.Close();

  return 0;
}