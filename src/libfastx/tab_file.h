#ifndef __TABULAR_FILE_H__
#define __TABULAR_FILE_H__

#include <string>

/*
   Single-End reader/writer
 */
typedef enum {
	TAB_FORMAT_UNKNOWN,
	TAB_FORMAT_FASTA,
	TAB_FORMAT_FASTQ
} TABULAR_FILE_FORMAT;


class TabularFileReader : public ISequenceReader
{
private:
	std::string _filename;
	generic_input_stream input_stream;
	size_t line_number;
	TABULAR_FILE_FORMAT input_file_format;

	int _ASCII_quality_offset ;

	std::string	cached_line;
	bool		have_cached_line;

	void detect_file_format();
	TABULAR_FILE_FORMAT detect_line_format(const std::string& line);

public:
	TabularFileReader ( const std::string& filename, int _ASCII_Quality_offset ) ;
	TabularFileReader ( input_stream_wrapper w, int _ASCII_Quality_offset  ) ;
	virtual bool read_next_sequence(Sequence& /*output*/) ;

	virtual ISequenceWriter* create_fastx_writer(const std::string& filename);
	virtual ISequenceWriter* create_tabular_writer(const std::string& filename);
};

class TabularFileWriter : public ISequenceWriter
{
private:
	std::string _filename;
	generic_output_stream output_stream;
	TABULAR_FILE_FORMAT output_file_format;

public:
	TabularFileWriter ( const std::string& filename, TABULAR_FILE_FORMAT _output_format ) ;
	virtual void write_sequence(const Sequence&) ;
};



/*
   Paired-End reader/writer
 */

class PE_TabularFileReader : public ISequenceReaderPE
{
private:
	std::string _filename;
	generic_input_stream input_stream;
	size_t line_number;

public:
	PE_TabularFileReader ( const std::string& filename ) ;
	PE_TabularFileReader ( input_stream_wrapper w ) ;
	virtual bool read_next_sequence(Sequence&, Sequence&) ;

	virtual ISequenceWriterPE* create_writer(const std::string& filename);
};

class PE_TabularFileWriter : public ISequenceWriterPE
{
private:
	std::string _filename;
	generic_output_stream output_stream;
public:
	PE_TabularFileWriter ( const std::string& filename ) ;
	virtual void write_sequence(const Sequence&) ;
};


#endif
