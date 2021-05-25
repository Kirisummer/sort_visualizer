#ifndef SORTMODEL_H
#define SORTMODEL_H

#include "sortdef.h"
#include <QObject>

#include <tuple>
#include <optional>

#include <mutex>
#include <condition_variable>


class SortModel : public QObject {
	Q_OBJECT
	public:
		explicit SortModel(QObject *parent = nullptr);
		bool isFinished() { return m_finished; }

	public slots:
		void run(const Array &array);
		void step();

	signals:
		void compared(uint i, uint j);
		void swapped(uint i, uint j);
		void reset(const Array &array);
		void finished();

	protected:
		virtual void sort() =0;
		const Array &array() const { return m_array; }
		void start();
		std::optional<bool> compare(uint i, uint j);
		bool swap(uint i, uint j);
		void finish();

	private:
		Array m_array;
		std::condition_variable lock;
		QThread *m_thread = nullptr;
		bool m_finished = false;

};

#endif // SORTMODEL_H
