#include "sortmodel.h"

#include <QThread>


SortModel::SortModel(QObject *parent): QObject(parent) {
}

void SortModel::run(const Array &array) {
	if (m_thread) {
		m_thread->requestInterruption();
		lock.notify_one();
		m_thread->wait();
		m_thread->deleteLater();
	}

	m_finished = false;
	m_array = array;
	m_thread = QThread::create([this](){ sort(); });
	emit reset(array);
}

void SortModel::step() {
	if (m_finished)
		return;

	if (m_thread->isRunning())
		lock.notify_one();
	else
		m_thread->start();
}

std::optional<bool> SortModel::compare(uint i, uint j) {
	std::mutex mutex;
	std::unique_lock unique(mutex);

	bool result = m_array.at(i) < m_array.at(j);
	emit compared(i, j);
	lock.wait(unique);
	if (QThread::currentThread()->isInterruptionRequested())
		return std::optional<bool>();
	return result;
}

bool SortModel::swap(uint i, uint j) {
	std::mutex mutex;
	std::unique_lock unique(mutex);

	std::swap(m_array[i], m_array[j]);
	emit swapped(i, j);
	lock.wait(unique);
	return QThread::currentThread()->isInterruptionRequested();
}

void SortModel::finish() {
	m_finished = true;
	emit finished();
}
