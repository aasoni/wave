#include <lf_wave_simulator_2d.h>

#include <math.h>

namespace aasoni {

//determine boundary type
void LFWaveSimulator2D::boundaryType(bool *corner, BOUNDARY_TYPE *bType, 
                                   CORNER_TYPE *cType, size_t i, size_t j)
{
    if(!corner || !bType || !cType)
        return; //invalid input

    if(i == 0) //lower boundary
    {
        if(j == 0)
        {
            *corner = true;
            *cType = BOTTOM_LEFT;
        }
        else if(j == m_xSize - 1)
        {
            *corner = true;
            *cType = BOTTOM_RIGHT;
        }
        else
        {
            *corner = false;
            *bType = LOWER;
        }
    }
    else if( i == m_ySize - 1) //upper boundary
    {
        if(j == 0)
        {
            *corner = true;
            *cType = TOP_LEFT;
        }
        else if(j == m_xSize - 1)
        {
            *corner = true;
            *cType = TOP_RIGHT;
        }
        else
        {
            *corner = false;
            *bType = UPPER;
        }
    }
    else //left & right boundaries
    {
        *corner = false;
        if(j == 0)
            *bType = LEFT;
        else
            *bType = RIGHT;
    }
}

//reflective boundary
double LFWaveSimulator2D::boundaryStep(size_t i, size_t j, BOUNDARY_TYPE type)
{
    //indexes
    size_t ipo = i+1, imo = i-1, jpo = j+1, jmo = j-1;
    switch(type)
    {
        case LEFT:
            jmo = jpo;
            break;
        case RIGHT:
            jpo = jmo;
            break;
        case LOWER:
            imo = ipo;
            break;
        case UPPER:
            ipo = imo;
            break;
        default:
            //invalid boundary
            return 0.0;
    }

    double avg = (*m_wave)[ipo][j] +
                 (*m_wave)[imo][j] +
                 (*m_wave)[i][jpo] +
                 (*m_wave)[i][jmo];
    double alpha = pow(m_lambdaX,2.0);
    return alpha*avg + 2.0*(1 - 2.0*alpha)*(*m_wave)[i][j];
}

//reflective boundary corner
double LFWaveSimulator2D::cornerStep(size_t i, size_t j, CORNER_TYPE type)
{
    //indexes
    size_t ipo = i+1, imo = i-1, jpo = j+1, jmo = j-1;
    switch(type)
    {
        case BOTTOM_LEFT:
            imo = ipo;
            jmo = jpo;
            break;
        case BOTTOM_RIGHT:
            imo = ipo;
            jpo = jmo;
            break;
        case TOP_LEFT:
            ipo = imo;
            jmo = jpo;
            break;
        case TOP_RIGHT:
            ipo = imo;
            jpo = jmo;
            break;
            break;
        default:
            //invalid corner
            return 0.0;
    }

    double avg = (*m_wave)[ipo][j] +
                 (*m_wave)[imo][j] +
                 (*m_wave)[i][jpo] +
                 (*m_wave)[i][jmo];
    double alpha = pow(m_lambdaX,2.0);
    return alpha*avg + 2.0*(1 - 2.0*alpha)*(*m_wave)[i][j];
}

//boundary step
double LFWaveSimulator2D::boundaryStep(size_t i, size_t j)
{
    if(i > 0 && i < m_ySize - 1 &&
       j > 0 && j < m_xSize - 1 )
        return internalStep(i,j); //skip internal point

    bool corner;
    BOUNDARY_TYPE bType;
    CORNER_TYPE cType;
    boundaryType(&corner, &bType, &cType, i, j);

    double val = 0.0;
    if(!corner)
        val = boundaryStep(i, j, bType);
    else 
        val = cornerStep(i, j, cType);

    return val;
}

//internal step
double LFWaveSimulator2D::internalStep(size_t i, size_t j)
{
    //handle boundary with land
    size_t ipo = i+1, imo = i-1, jpo = j+1, jmo = j-1;
    if(isnan((*m_wave)[i+1][j]))
        ipo = imo;
    if(isnan((*m_wave)[i-1][j]))
        imo = ipo;
    if(isnan((*m_wave)[i][j+1]))
        jpo = jmo;
    if(isnan((*m_wave)[i][j-1]))
        jmo = jpo;

    double avg = (*m_wave)[ipo][j] +
                 (*m_wave)[imo][j] +
                 (*m_wave)[i][jpo] +
                 (*m_wave)[i][jmo];

    double alpha = pow(m_lambdaX,2.0);
    return alpha*avg + 2.0*(1 - 2.0*alpha)*(*m_wave)[i][j];
}

bool LFWaveSimulator2D::next()
{
    if(!m_prevWave || !m_wave || m_steps == 0)
        return false;

    //surface values
    MAT &U = *m_wave;
    MAT &prevU = *m_prevWave;
    MAT nextU = U;
    m_nextWave = &nextU;

    //update internal points
    for(size_t i = 1; i < m_ySize - 1; ++i)
    {
        for(size_t j = 1; j < m_xSize - 1; ++j)
        {
            if(isnan(U[i][j]))
                continue;

            double val = internalStep(i,j) - prevU[i][j];
            nextU[i][j] = val;
        }
    }

    //update boundary points
    for(size_t i = 0; i < m_ySize; ++i)
    {
        if(i == 0 || i == m_ySize - 1)
        {
            for(size_t j = 0; j < m_xSize; ++j)
            {
                if(isnan(U[i][j]))
                    continue;
                nextU[i][j] = boundaryStep(i,j) - prevU[i][j];
            }
        }
        size_t e = m_xSize - 1;
        nextU[i][0] = boundaryStep(i,0) - prevU[i][0];
        nextU[i][e] = boundaryStep(i,e) - prevU[i][e];
    }

    //update previous
    prevU = U;
    U = nextU;

    //decrement steps
    --m_steps;

    return true;
}

}
