#include "informations_client_stagiaire.h"

informations_client_stagiaire::informations_client_stagiaire(QObject *parent)
    : QAbstractItemModel(parent)
{}

QVariant informations_client_stagiaire::headerData(int section,
                                                   Qt::Orientation orientation,
                                                   int role) const
{
    // FIXME: Implement me!
}

QModelIndex informations_client_stagiaire::index(int row,
                                                 int column,
                                                 const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex informations_client_stagiaire::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int informations_client_stagiaire::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int informations_client_stagiaire::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant informations_client_stagiaire::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
