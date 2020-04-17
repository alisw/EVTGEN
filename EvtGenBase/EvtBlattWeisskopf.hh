#ifndef EVT_BLATT_WEISSKOPF_HH
#define EVT_BLATT_WEISSKOPF_HH

// Blatt-Weisskopf penetration form factor for a resonance R->AB.
// Taken from CLEO preprint 00-23 (hep-ex/0011065)

class EvtBlattWeisskopf {
  public:
    EvtBlattWeisskopf( int LL, double R, double p0 );
    EvtBlattWeisskopf( const EvtBlattWeisskopf& );

    double operator()( double p ) const;

  private:
    int _LL;           // angular momentum of daughters
    double _radial;    // resonance radial parameter
    double _p0;

    double _F0;    // formula evaluated at _p0
    double compute( double p ) const;
};

#endif
