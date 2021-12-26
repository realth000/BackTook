#  Copyright (C) 2021 realth000 <a598919335@gmail.com>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.

target_sources(BackTook PRIVATE main.cpp)
target_sources(BackTook PRIVATE btmaincontroller.h btmaincontroller.cpp)
target_sources(BackTook PRIVATE jsonparser.h jsonparser.cpp)
target_sources(BackTook PRIVATE backupprogressworker.h backupprogressworker.cpp)
