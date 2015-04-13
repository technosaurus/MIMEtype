/* sort by magic in ascii order @ offset 0 for memcmp. A-Z comes before a-z
 * 1st char in magic (1st) string is the length in hex
 * followed by major and minor type strings
 * 1st char in mime (2nd) string indicates the major type in hex (using defined types)
 *
 * "<len>" "<Magic>", MAJOR-TYPE "minor-type"
 */

static const char *mimes0[] = {
	"\x05" "\x00\x01\x00\x00\x00", APPLICATION "x-font-ttf",
	"\x0C" "\x04%!PS-Adobe-", APPLICATION "postscript",
	"\x0D" "\x1B%-12345X%!PS", APPLICATION "postscript",
	"\x02" "\x1F\x8B", APPLICATION "x-gzip",
	"\x02" "\x1F\x9D", APPLICATION "x-compress",
	"\x0E" "!<arch>""\x0A""debian", APPLICATION "x-debian-package",
	"\x08" "#! rnews", MESSAGE "rfc822",
	"\x0A" "#!/bin/ash", APPLICATION "x-shellscript",
	"\x0B" "#!/bin/bash", APPLICATION "x-shellscript",
	"\x0B" "#!/bin/perl", TEXT "x-perl",
	"\x09" "#!/bin/sh", APPLICATION "x-shellscript",
	"\x12" "#!/usr/bin/env lua", TEXT "x-lua",
	"\x0F" "#!/usr/bin/perl", TEXT "x-perl",
	"\x15" "#!/usr/bin/env python", TEXT "x-python",
	"\x13" "#!/usr/bin/env ruby", TEXT "x-ruby",
	"\x12" "#!/usr/bin/env tcl", TEXT "x-tcl",
	"\x13" "#!/usr/bin/env wish", TEXT "x-tcl",
	"\x0E" "#!/usr/bin/lua", TEXT "x-lua",
	"\x11" "#!/usr/bin/python", TEXT "x-python",
	"\x0F" "#!/usr/bin/ruby", TEXT "x-ruby",
	"\x0E" "#!/usr/bin/tcl", TEXT "x-tcl",
	"\x0F" "#!/usr/bin/wish", TEXT "x-tcl",
	"\x14" "#!/usr/local/bin/lua", TEXT "x-lua",
	"\x15" "#!/usr/local/bin/perl", TEXT "x-perl",
	"\x17" "#!/usr/local/bin/python", TEXT "x-python",
	"\x15" "#!/usr/local/bin/ruby", TEXT "x-ruby",
	"\x14" "#!/usr/local/bin/tcl", TEXT "x-tcl",
	"\x15" "#!/usr/local/bin/wish", TEXT "x-tcl",
	"\x11" "# KDE Config File", APPLICATION "x-kdelnk",
	"\x14" "# PaCkAgE DaTaStReAm", APPLICATION "x-svr4-package",
	"\x06" "# xmcd", TEXT "x-xmcd",
	"\x0B" "#?RADIANCE\x0A", IMAGE "vnd.radiance",
	"\x0B" "%!PS-Adobe-", APPLICATION "postscript",
	"\x05" "%PDF-", APPLICATION "pdf",
	"\x05" "*mbx*", APPLICATION "mbox",
	"\x1C" "-----BEGIN PGP MESSAGE-\x00\x1E---", APPLICATION "pgp",
	"\x1E" "-----BEGIN PGP SIGNATURE-\x00\x03.\"", APPLICATION "pgp-signature",
	"\x03" ".\"", TEXT "troff",
	"\x04" ".sd\x00", AUDIO "x-dec-basic",
	"\x04" ".snd", AUDIO "basic",
	"\x09" "/* XPM */", IMAGE "x-xpmi",
	"\x05" "07070", APPLICATION "x-cpio",
	"\x04" "1\xBE\x00\x00", APPLICATION "msword",
	"\x06" "7z\xBC\xAF'\x1C", APPLICATION "x-7z-compressed",
	"\x1A" "8BPS Adobe Photoshop Image", IMAGE "vnd.adobe.photoshop",
	"\x04" ";ELC", APPLICATION "x-elc",
	"\x0E" "<!DOCTYPE HTML", TEXT "html",
	"\x0E" "<?xml version=", APPLICATION "xml",
	"\x06" "<Book ", APPLICATION "x-mif",
	"\x09" "<BookFile", APPLICATION "x-mif",
	"\x04" "<MML", APPLICATION "x-mif",
	"\x08" "<MIFFile", APPLICATION "x-mif",
	"\x10" "<MakerDictionary", APPLICATION "x-mif",
	"\x06" "<Maker", APPLICATION "x-mif",
	"\x0C" "<SCRIBUSUTF8", APPLICATION "x-scribus",
	"\x0C" "<map version", APPLICATION "x-freemind",
	"\x0A" "@ echo off", TEXT "x-msdos-batch",
	"\x09" "@echo off", TEXT "x-msdos-batch",
	"\x04" "@rem", TEXT "x-msdos-batch",
	"\x04" "@set", TEXT "x-msdos-batch",
	"\x04" "ADIF", AUDIO "x-hx-aac-adif",
	"\x08" "AT&TFORM", IMAGE "vnd.djvu",
	"\x07" "Article", MESSAGE "news",
	"\x0F" "BEGIN:VCALENDAR", TEXT "calendar",
	"\x0B" "BEGIN:VCARD", TEXT "x-vcard",
	"\x04" "BM\x00\x03", IMAGE "x-ms-bmp",
	"\x03" "BZh", APPLICATION "x-bzip2",
	"\x04" "CPC\xB2", IMAGE "x-cpi",
	"\x03" "CWS", APPLICATION "x-shockwave-flash",
	"\x04" "DICM", APPLICATION "dicom",
	"\x04" "EIM ", IMAGE "x-eim",
	"\x06" "FGF95a", IMAGE "x-unknown",
	"\x03" "FLV", VIDEO "x-flv",
	"\x04" "FOVb", IMAGE "x-x3f",
	"\x03" "FWS", APPLICATION "x-shockwave-flash",
	"\x0A" "Forward to", MESSAGE "rfc822",
	"\x05" "From:", MESSAGE "rfc822",
	"\x04" "GIF8", IMAGE "gif",
	"\x06" "GIF94z", IMAGE "x-unknown",
	"\x0A" "HEADER    ", CHEMICAL "x-pdb",
	"\x11" "HWP Document File", APPLICATION "x-hwp",
	"\x0E" "II\x1A\x00\x00\x00HEAPCCDR", IMAGE "x-canon-crw",
	"\x04" "II*\x00", IMAGE "tiff",
	"\x0A" "II*\x00\x10\x00\x00\x00CR", IMAGE "x-canon-cr2",
	"\x04" "IIN1", IMAGE "x-niff",
	"\x04" "IIRO", IMAGE "x-olympus-orf",
	"\x04" "IIRS", IMAGE "x-olympus-orf",
	"\x04" "LRZI", APPLICATION "x-lrzip",
	"\x04" "LZIP", APPLICATION "x-lzip",
	"\x0E" "MAS_UTrack_V00", AUDIO "x-mod",
	"\x04" "MM\x00*", IMAGE "tiff",
	"\x04" "MMOR", IMAGE "x-olympus-orf",
	"\x04" "MOVI", VIDEO "x-sgi-movie",
	"\x04" "MThd", AUDIO "midi",
	"\x02" "MZ", APPLICATION "x-dosexec",
	"\x09" "N#! rnews", MESSAGE "rfc822",
	"\x04" "OTTO", APPLICATION "vnd.ms-opentype",
	"\x04" "OggS", APPLICATION "ogg",
	"\x03" "P4\x00", IMAGE "x-portable-bitmap",
	"\x03" "P5\x00", IMAGE "x-portable-greymap",
	"\x03" "P6\x00", IMAGE "x-portable-pixmap",
	"\x03" "P7\x00", IMAGE "x-portable-pixmap",
	"\x0C" "P7\n#MTPAINT#", IMAGE "x-portable-multimap",
	"\x03" "PBF", IMAGE "x-unknown",
	"\x04" "PDN3", IMAGE "x-paintnet",
	"\x05" "PFS1\x0A", IMAGE "x-pfs",
	"\x04" "PK\x03\x04", APPLICATION "zip",
	"\x08" "PK\x07\x08PK\x03\x04", APPLICATION "zip",
	"\x08" "PK00PK\x03\x04", APPLICATION "zip",
	"\x05" "PO^Q`", APPLICATION "msword",
	"\x05" "Path:", MESSAGE "news",
	"\x07" "Pipe to", MESSAGE "rfc822",
	"\x10" "RF64\xFF\xFF\xFF\xFFWAVEds64", AUDIO "x-wav",
	"\x04" "Rar!", APPLICATION "x-rar",
	"\x09" "Received:", MESSAGE "rfc822",
	"\x0E" "Relay-Version:", MESSAGE "rfc822",
	"\x0C" "Return-Path:", MESSAGE "rfc822",
	"\x04" "SIT!", APPLICATION "x-stuffit",
	"\x0D" "SplineFontDB:", APPLICATION "vnd.font-fontforge-sfd",
	"\x08" "StuffIt\x00", APPLICATION "x-stuffit",
	"\x04" "WARC", APPLICATION "warc",
	"\x04" "Xcur", IMAGE "x-xcursor",
	"\x05" "Xref:", MESSAGE "news",
	"\x13" "[KDE Desktop Entry]", APPLICATION "x-kdelnk",
	"\x0B" "d8:announce", APPLICATION "x-bittorrent",
	"\x04" "drpm", APPLICATION "x-rpm",
	"\x04" "fLaC", AUDIO "x-flac",
	"\x0B" "filedesc://", APPLICATION "x-ia-arc",
	"\x10" "riff.\x91\xCF\x11\xA5\xD6(\xDB\x04\xC1\x00\x00", AUDIO "x-w64",
	"\x05" "\rtf\x00", TEXT "rtf",
	"\x09" "\x89LZO\x00\x0D\x0A\x1A\x0A", APPLICATION "x-lzop",
	"\x08" "\x89PNG\x0D\x0A\x1A\x0A", IMAGE "png",
	"\x04" "\x8AJNG", VIDEO "x-jng",
	"\x04" "\x8AMNG", VIDEO "x-mng",
	"\x08" "\x89HDF\x0D\x0A\x1A\x0A", APPLICATION "x-hdf",
	"\x04" "\xCE\xCE\xCE\xCE", APPLICATION "x-java-jce-keystore",
	"\x06" "\xFD""7zXZ\x00", APPLICATION "x-xz",
	"\x04" "\xFE""7\x00#", APPLICATION "msword",
	"\x02" "\xFF\xD8", IMAGE "jpeg",
	"\x04" "\xFF\xD8\xFF\xE0", IMAGE "jpeg",
	"\x04" "\xFF\xD8\xFF\xEE", IMAGE "jpeg",
};
