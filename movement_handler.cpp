#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "main.cpp" // Inclua a referência ao arquivo principal que contém as estruturas de dados
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>

// Verifica se um movimento é válido
bool isValidMove(const Piece &piece, int targetX, int targetZ, bool isWhiteTurn, const std::vector<Piece> &pieces)
{
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;

    // Verifica se está dentro do tabuleiro
    if (targetX < 0 || targetX >= 8 || targetZ < 0 || targetZ >= 8)
    {
        return false;
    }

    // Verifica se a casa de destino está vazia
    for (const auto &p : pieces)
    {
        if (p.pos.x == targetX && p.pos.z == targetZ)
        {
            return false;
        }
    }

    // Movimento normal (para frente)
    if (!piece.isKing)
    {
        if (piece.isWhite && deltaZ == -1 && std::abs(deltaX) == 1)
        {
            return true;
        }
        else if (!piece.isWhite && deltaZ == 1 && std::abs(deltaX) == 1)
        {
            return true;
        }
    }
    else
    { // Movimento para damas
        if (std::abs(deltaX) == std::abs(deltaZ))
        {
            return true;
        }
    }

    // Movimento de captura
    if (std::abs(deltaX) == 2 && std::abs(deltaZ) == 2)
    {
        int midX = piece.pos.x + deltaX / 2;
        int midZ = piece.pos.z + deltaZ / 2;
        for (const auto &p : pieces)
        {
            if (p.pos.x == midX && p.pos.z == midZ && p.isWhite != piece.isWhite)
            {
                return true;
            }
        }
    }

    return false;
}

// Move a peça
void movePiece(Piece &piece, int targetX, int targetZ, std::vector<Piece> &pieces, bool &isWhiteTurn)
{
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;

    // Verifica se é um movimento de captura
    if (std::abs(deltaX) == 2 && std::abs(deltaZ) == 2)
    {
        int midX = piece.pos.x + deltaX / 2;
        int midZ = piece.pos.z + deltaZ / 2;
        auto it = std::find_if(pieces.begin(), pieces.end(), [midX, midZ](const Piece &p)
                               { return p.pos.x == midX && p.pos.z == midZ; });
        if (it != pieces.end())
        {
            // Remove a peça capturada
            pieces.erase(it);
        }
    }

    // Move a peça para o destino
    piece.pos.x = targetX;
    piece.pos.z = targetZ;

    // Verifica se a peça deve ser promovida a dama
    if ((piece.isWhite && targetZ == 0) || (!piece.isWhite && targetZ == 7))
    {
        piece.isKing = true;
    }

    // Alterna o turno
    isWhiteTurn = !isWhiteTurn;
}

#endif // MOVEMENT_HANDLER_H
