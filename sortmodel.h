#ifndef SORTMODEL_H
#define SORTMODEL_H

#include "sortdef.h"
#include <QObject>
#include <tuple>

class SortModel : public QObject {
	Q_OBJECT
	public:
		explicit SortModel(QObject *parent = nullptr): QObject(parent) {}

		const Array &array() const { return m_array; }
		std::tuple <SortAction, uint, uint> lastAction() const { return m_lastAction; }
		bool compareResult() const { return m_compareResult; }
		bool isFinished() const { return m_finished; }

	public slots:
		virtual void setArray(const Array &new_array) {
			m_array = new_array;
			emit arraySet(new_array);
		}
		virtual void step() =0;

	signals:
		void arraySet(const Array &);
		void swapped(uint, uint);
		void compared(uint, uint);
		void finished();

	protected:
		bool compare(uint i, uint j) {
			m_compareResult = m_array.at(i) < m_array.at(j);
			m_lastAction = std::make_tuple(SortAction::Compare, i, j);
			emit compared(i, j);
			return m_compareResult;
		}

		void swap(uint i, uint j) {
			std::swap(m_array[i], m_array[j]);
			m_lastAction = std::make_tuple(SortAction::Swap, i, j);
			emit swapped(i, j);
		}

		void nop() {
			m_lastAction = std::make_tuple(SortAction::None, 0, 0);
		}

		void finish() {
			m_finished = true;
			emit finished();
		}

	private:
		Array m_array;
		std::tuple <SortAction, uint, uint> m_lastAction;
		bool m_compareResult;
		bool m_finished;

};

#endif // SORTMODEL_H
