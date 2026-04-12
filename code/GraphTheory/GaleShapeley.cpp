// Checks if woman 'w' prefers 'm1' over 'm'
bool wPrefersM1OverM(vector<vector<int>> &prefer, int w, int m, int m1)
{
    int N = prefer[0].size();
    for (int i = 0; i < N; i++)
    {
        // If m1 comes before m, w prefers
        // her current engagement
        if (prefer[w][i] == m1)
            return true;

        // If m comes before m1, w prefers m
        if (prefer[w][i] == m)
            return false;
    }
}

// Implements the stable marriage algorithm
vector<int> stableMarriage(vector<vector<int>> &prefer)
{
    int N = prefer[0].size();

    // Stores women's partners
    vector<int> wPartner(N, -1);

    // Tracks free men
    vector<bool> mFree(N, false);
    int freeCount = N;

    while (freeCount > 0)
    {
        int m;
        for (m = 0; m < N; m++)
            if (!mFree[m])
                break;

        // Process each woman in m's preference list
        for (int i = 0; i < N && !mFree[m]; i++)
        {
            int w = prefer[m][i];
            if (wPartner[w - N] == -1)
            {
                // Engage m and w if w is free
                wPartner[w - N] = m;
                mFree[m] = true;
                freeCount--;
            }
            else
            {
                int m1 = wPartner[w - N];
                // If w prefers m over her current partner, reassign
                if (!wPrefersM1OverM(prefer, w, m, m1))
                {
                    wPartner[w - N] = m;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            }
        }
    }
    return wPartner;
}