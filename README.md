# mod-attunement-skip

A companion module for [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) that automatically grants raid attunement items and completes attunement quests when players reach the appropriate level threshold.

## Features

- Automatically sends attunement items via in-game mail when players reach level 60 or 70
- Auto-completes attunement quests required for raid entry (Naxx40, SSC, Hyjal)
- Works alongside mod-individual-progression without requiring modifications to it
- Configurable per-item and per-quest toggles
- Items sent via mail so they are received even with full bags

## Installation

1. Clone this module into your AzerothCore `modules/` directory:
   ```bash
   cd azerothcore/modules
   git clone https://github.com/your-repo/mod-attunement-skip.git
   ```

2. Rebuild AzerothCore:
   ```bash
   cd build
   cmake .. -DMODULES=static
   make -j$(nproc)
   make install
   ```

3. Configure options in `etc/mod-attunement-skip.conf.dist` (or copy to `mod-attunement-skip.conf` for custom overrides).

4. Restart your worldserver.

## Configuration

All options are in `mod-attunement-skip.conf.dist`:

| Option | Default | Description |
|--------|---------|-------------|
| `AttunementSkip.Enable` | 1 | Master toggle |
| `AttunementSkip.DrakefireAmulet` | 1 | Grant Drakefire Amulet at level 60 |
| `AttunementSkip.OnyxiaScaleCloak` | 1 | Grant Onyxia Scale Cloak at level 60 |
| `AttunementSkip.KeyToKarazhan` | 1 | Grant Key to Karazhan at level 70 |
| `AttunementSkip.TempestKey` | 1 | Grant Tempest Key at level 70 |
| `AttunementSkip.MedallionOfKarabor` | 1 | Grant Medallion of Karabor at level 70 |
| `AttunementSkip.Naxx40Attunement` | 1 | Auto-complete Naxx40 attunement quests at level 60 |
| `AttunementSkip.CudgelOfKarDesh` | 1 | Auto-complete Cudgel of Kar'desh quest at level 70 |
| `AttunementSkip.VialsOfEternity` | 1 | Auto-complete Vials of Eternity quest at level 70 |

## Items Granted

| Level | Item | Entry ID | Required For |
|-------|------|----------|--------------|
| 60 | Drakefire Amulet | 16309 | Onyxia's Lair |
| 60 | Onyxia Scale Cloak | 18422 | BWL Shadow Flame protection |
| 70 | Key to Karazhan | 24490 | Karazhan |
| 70 | Tempest Key | 31704 | The Eye |
| 70 | Medallion of Karabor | 32649 | Black Temple |

## Quests Auto-Completed

| Quest | Entry ID | Required For |
|-------|----------|--------------|
| The Archangel's Payload | 9121 | Naxxramas 40 |
| Echoes of War | 9122 | Naxxramas 40 |
| The Only Song I Know... | 9123 | Naxxramas 40 |
| The Cudgel of Kar'desh | 10901 | Serpentshrine Cavern |
| The Vials of Eternity | 10445 | Mount Hyjal |

## Compatibility

- Designed to work with mod-individual-progression but functions independently
- WotLK raids (Naxx10/25, Ulduar, ToC, ICC, RS) have no attunement requirements in 3.3.5a
- No database changes required

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
